#include "tests.h"
#include "image.h"
#include "brightnessContrastAdjustment.h"
#include "gammaCorrection.h"
#include "imageConvolution.h"
#include "kernels.h"
#include "drawing.h"
#include <assert.h>
#include <sstream>

void testConstructors() {
	std::cout << "Testing constructors\n";

	Image img1;
	assert(img1.isEmpty());
	assert(img1.width() == 0);
	assert(img1.height() == 0);

	Image img2(100, 300);
	assert(!img2.isEmpty());
	assert(img2.width() == 100);
	assert(img2.height() == 300);

	Image img3(0, 0);
	assert(img3.isEmpty());

	Image img4(img2);
	assert(!img4.isEmpty());
	assert(img4.width() == 100);
	assert(img4.height() == 300);

	img3 = img2;
	assert(!img3.isEmpty());
	assert(img3.width() == 100);
	assert(img3.height() == 300);
}

void testPixelAccess() {
	std::cout << "Testing pixel access\n";

	Image img(10, 10);
	img.at(5, 5) = 200;
	assert(img.at(5, 5) == 200);

	try {
		img.at(10, 5);
		assert(false);
	}
	catch (const std::invalid_argument&) {}

	try {
		img.at(5, 10);
		assert(false);
	}
	catch (const std::invalid_argument&) {}

	uint8_t* row = img.row(5);
	row[5] = 150;
	assert(img.at(5, 5) == 150);

	img = img.zeros(10, 10);
	assert(img.at(0, 0) == 0);
	assert(img.at(9, 9) == 0);
	assert(img.at(5, 8) == 0);

	img = img.ones(10, 10);
	assert(img.at(0, 0) == 1);
	assert(img.at(9, 9) == 1);
	assert(img.at(5, 8) == 1);
}

void testImageOperations() {
	std::cout << "Testing image operations\n";

	Image img1(2, 2);
	Image img2(2, 2);

	img1.at(0, 0) = 100; img1.at(0, 1) = 50;
	img1.at(1, 0) = 200; img1.at(1, 1) = 150;

	img2.at(0, 0) = 50; img2.at(0, 1) = 100;
	img2.at(1, 0) = 100; img2.at(1, 1) = 50;

	Image result = img1 + img2;
	assert(result.at(0, 0) == 150);
	assert(result.at(0, 1) == 150);
	assert(result.at(1, 0) == 255);
	assert(result.at(1, 1) == 200);

	Image add = img1 + 50;
	assert(add.at(0, 0) == 150);
	assert(add.at(0, 1) == 100);
	assert(add.at(1, 0) == 250);
	assert(add.at(1, 1) == 200);

	result = img1 - img2;
	assert(result.at(0, 0) == 50);
	assert(result.at(0, 1) == 0);
	assert(result.at(1, 0) == 100);
	assert(result.at(1, 1) == 100);

	Image subtract = img1 - 100;
	assert(subtract.at(0, 0) == 0);
	assert(subtract.at(0, 1) == 0);
	assert(subtract.at(1, 0) == 100);
	assert(subtract.at(1, 1) == 50);

	Image multiplication = img1 * 2;
	assert(multiplication.at(0, 0) == 200);
	assert(multiplication.at(0, 1) == 100);
	assert(multiplication.at(1, 0) == 255);
	assert(multiplication.at(1, 1) == 255);
}

void testFileIO() {
	std::cout << "Testing file I/O\n";

	Image img(2, 2);
	img.at(0, 0) = 0; img.at(0, 1) = 127;
	img.at(1, 0) = 255; img.at(1, 1) = 64;

	assert(img.save("output.ascii.pgm"));

	Image loaded;
	assert(loaded.load("output.ascii.pgm"));

	assert(loaded.width() == 2);
	assert(loaded.height() == 2);
	assert(loaded.at(0, 0) == 0);
	assert(loaded.at(0, 1) == 127);
	assert(loaded.at(1, 0) == 255);
	assert(loaded.at(1, 1) == 64);
}

void testBrightnessAdjustment() {
	std::cout << "Testing brightness adjustment\n";

	Image src(2, 2);
	src.at(0, 0) = 100; src.at(0, 1) = 150;
	src.at(1, 0) = 50;  src.at(1, 1) = 200;

	Image dst;
	BrightnessContrastAdjustment identity(1.0f, 0.0f);
	identity.process(src, dst);
	assert(dst.at(0, 0) == 100);
	assert(dst.at(0, 1) == 150);
	assert(dst.at(1, 0) == 50);
	assert(dst.at(1, 1) == 200);

	BrightnessContrastAdjustment brighter(1.0f, 50.0f);
	brighter.process(src, dst);
	assert(dst.at(0, 0) == 150);
	assert(dst.at(0, 1) == 200);
	assert(dst.at(1, 0) == 100);
	assert(dst.at(1, 1) == 250);

	BrightnessContrastAdjustment higherContrast(2.0f, 0.0f);
	higherContrast.process(src, dst);
	assert(dst.at(0, 0) == 200);
	assert(dst.at(0, 1) == 255); 
	assert(dst.at(1, 0) == 100);
	assert(dst.at(1, 1) == 255);

	Image empty;
	try {
		brighter.process(empty, dst);
		assert(false);
	}
	catch (const std::invalid_argument&) {}
}

void testGammaCorrection() {
	std::cout << "Testing gamma correction\n";

	Image src(2, 2);
	src.at(0, 0) = 100; src.at(0, 1) = 200;
	src.at(1, 0) = 50;  src.at(1, 1) = 10;

	Image dst;

	GammaCorrection identity(1.0f);
	identity.process(src, dst);
	assert(dst.at(0, 0) == 100);
	assert(dst.at(0, 1) == 200);
	assert(dst.at(1, 0) == 50);
	assert(dst.at(1, 1) == 10);

	GammaCorrection brighten(0.5f);
	brighten.process(src, dst);
	assert(dst.at(0, 0) == static_cast<uint8_t>(std::pow(100, 0.5f)));
	assert(dst.at(0, 1) == static_cast<uint8_t>(std::pow(200, 0.5f)));
	assert(dst.at(1, 0) == static_cast<uint8_t>(std::pow(50, 0.5f)));
	assert(dst.at(1, 1) == static_cast<uint8_t>(std::pow(10, 0.5f)));

	Image empty;
	try {
		brighten.process(empty, dst);
		assert(false);
	}
	catch (const std::invalid_argument&) {}
}

void testConvolution() {
	std::cout << "Testing image convolution\n";

	// identity
	Image src(3, 3);
	src.at(0, 0) = 10; src.at(0, 1) = 20; src.at(0, 2) = 30;
	src.at(1, 0) = 40; src.at(1, 1) = 50; src.at(1, 2) = 60;
	src.at(2, 0) = 70; src.at(2, 1) = 80; src.at(2, 2) = 90;

	Image dst;

	ImageConvolution conv(3, 3, identity::kernel, identity::scale);
	conv.process(src, dst);

	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			assert(src.at(i, j) == dst.at(i, j));
		}
	}

	// mean blur
	src.at(0, 0) = 10; src.at(0, 1) = 10; src.at(0, 2) = 10;
	src.at(1, 0) = 10; src.at(1, 1) = 50; src.at(1, 2) = 10;
	src.at(2, 0) = 10; src.at(2, 1) = 10; src.at(2, 2) = 10;

	ImageConvolution conv2(3, 3, meanBlur::kernel, meanBlur::scale);
	conv2.process(src, dst);

	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			assert(dst.at(i, j) == 14);
		}
	}

	// gaussian blur
	ImageConvolution conv3(3, 3, gaussianBlur::kernel, gaussianBlur::scale);
	conv3.process(src, dst);
	assert(dst.at(1, 1) == 20);
	assert(dst.at(0, 1) == 15);
	assert(dst.at(1, 0) == 15);
	assert(dst.at(0, 0) == 12);
}

void testPoint() {
	std::cout << "Testing point\n";

	Point p1;
	assert(p1.x == 0 && p1.y == 0);

	Point p2(10, 20);
	assert(p2.x == 10 && p2.y == 20);

	std::ostringstream oss{};
	oss << p2;
	assert(oss.str() == "10 20\n");

	std::istringstream iss("30 40");
	Point p3;
	iss >> p3;
	assert(p3.x == 30 && p3.y == 40);
}

void testRectangle() {
	std::cout << "Testing rectangle\n";

	Rectangle r1;
	assert(r1.x == 0 && r1.y == 0 && r1.width == 0 && r1.height == 0);

	Rectangle r2(10, 20, 30, 40);
	assert(r2.x == 10 && r2.y == 20 && r2.width == 30 && r2.height == 40);

	Rectangle r3(Point(5, 5), Point(15, 25));
	assert(r3.x == 5 && r3.y == 5 && r3.width == 20 && r3.height == 10);

	std::ostringstream oss;
	oss << r2;
	assert(oss.str() == "10 20 \n30 40\n");

	std::istringstream iss("1 2 3 4");
	Rectangle r4;
	iss >> r4;
	assert(r4.x == 1 && r4.y == 2 && r4.width == 3 && r4.height == 4);

	Rectangle r5 = r2 + Point(5, 5);
	assert(r5.x == 15 && r5.y == 25 && r5.width == 30 && r5.height == 40);

	Rectangle r6 = r2 - Point(5, 5);
	assert(r6.x == 5 && r6.y == 15 && r6.width == 30 && r6.height == 40);

	Rectangle a(0, 0, 10, 10);
	Rectangle b(5, 5, 10, 10);

	Rectangle intersection = a & b;
	assert(intersection.x == 5 && intersection.y == 5 &&
		intersection.width == 5 && intersection.height == 5);

	Rectangle union_ = a | b;
	assert(union_.x == 0 && union_.y == 0 &&
		union_.width == 15 && union_.height == 15);
}

void testDrawing() {
	std::cout << "Testing drawing\n";
	Image img(20, 20);

	Image empty;
	try {
		Drawing::drawCircle(empty, Point(10, 10), 5, 255);
		assert(false);
	}
	catch (const std::invalid_argument&) {}

	try {
		Drawing::drawLine(empty, Point(0, 0), Point(10, 10), 255);
		assert(false); 
	}
	catch (const std::invalid_argument&) {}

	try {
		Drawing::drawRectangle(empty, Rectangle(0, 0, 10, 10), 255);
		assert(false); 
	}
	catch (const std::invalid_argument&) {}

	Drawing::drawCircle(img, Point(10, 10), 5, 255);
	assert(img.at(10, 15) == 255);
	assert(img.at(10, 5) == 255); 
	assert(img.at(15, 10) == 255);
	assert(img.at(5, 10) == 255); 

	Drawing::drawLine(img, Point(0, 0), Point(19, 19), 200);
	assert(img.at(0, 0) == 200);
	assert(img.at(10, 10) == 200);
	assert(img.at(19, 19) == 200);

	Drawing::drawRectangle(img, Rectangle(2, 2, 5, 5), 150);
	assert(img.at(2, 2) == 150);
	assert(img.at(2, 7) == 150);
	assert(img.at(7, 2) == 150);
	assert(img.at(7, 7) == 150); 

	Drawing::drawRectangle(img, Point(12, 12), Point(17, 17), 100);
	assert(img.at(12, 12) == 100);
	assert(img.at(12, 17) == 100);
	assert(img.at(17, 12) == 100);
	assert(img.at(17, 17) == 100);

}
void testAll(){
	testConstructors();
	testPixelAccess();
	testImageOperations();
	testFileIO();
	testBrightnessAdjustment();
	testGammaCorrection();
	testConvolution();
	testPoint();
	testRectangle();
	testDrawing();
}
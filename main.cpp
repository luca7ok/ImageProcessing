#define _CRT_DBG_MALLOC
#include "image.h"

int main() {
	try {
		Image image1, image2;
		image1.load("inputImages/coins.ascii.pgm");
		image1.save("output.ascii.pgm");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
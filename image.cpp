#include "image.h"
#include <fstream>
#include <sstream>
#include <exception>

Image::Image() {
	this->m_data = nullptr;
	this->m_width = 0;
	this->m_height = 0;
}

Image::Image(unsigned int w, unsigned int h) {
	this->m_width = w;
	this->m_height = h;
	if (this->m_width == 0 || this->m_height == 0) {
		this->m_width = 0;
		this->m_height = 0;
		this->m_data = nullptr;
	}
	else {
		this->m_data = new uint8_t* [this->m_height];
		for (unsigned int i = 0; i < this->m_height; i++) {
			this->m_data[i] = new uint8_t[this->m_width];
		}
	}
}

Image::Image(const Image& other) {
	this->m_width = other.m_width;
	this->m_height = other.m_height;

	this->m_data = new uint8_t* [this->m_height];
	for (unsigned int i = 0; i < this->m_height; i++) {
		this->m_data[i] = new uint8_t[this->m_width];

		for (unsigned int j = 0; j < this->m_width; j++) {
			this->m_data[i][j] = other.m_data[i][j];
		}
	}
}

void Image::release() {
	if (this->m_data) {
		for (unsigned int i = 0; i < this->m_height; i++) {
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}
}

Image::~Image() {
	release();
}

Image& Image::operator=(const Image& other) {
	if (this != &other) {
		release();

		this->m_width = other.m_width;
		this->m_height = other.m_height;

		this->m_data = new uint8_t* [this->m_height];
		for (unsigned int i = 0; i < this->m_height; i++) {
			this->m_data[i] = new uint8_t[this->m_width];

			for (unsigned int j = 0; j < this->m_width; j++) {
				this->m_data[i][j] = other.m_data[i][j];
			}
		}
	}
	return *this;
}

unsigned int Image::width() const {
	return this->m_width;
}

unsigned int Image::height() const {
	return this->m_height;
}

Size Image::size() const {
	return Size(this->m_width, this->m_height);
}

bool Image::load(std::string imagePath) {
	std::ifstream file(imagePath);
	if (!file.is_open()) {
		throw std::invalid_argument("Error: Could not open the file");
		return false;
	}

	std::string line;
	std::string magicNumber;
	unsigned int width = 0, height = 0;

	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#')
			continue;

		std::istringstream iss(line);
		iss >> magicNumber;
		
		if (magicNumber == "P2" || magicNumber == "P5") {
			while (std::getline(file, line)) {
				if (line.empty() || line[0] == '#')
					continue;
				std::istringstream dim(line);
				dim >> this->m_width>>this->m_height;
				break;
			}

			while (std::getline(file, line)) {
				if (line.empty() || line[0] == '#')
					continue;
				std::istringstream max(line);
				unsigned int maxValue;
				max >> maxValue;
				break;
			}

			break;
		}
		else {
			throw std::invalid_argument("Invalid PGM format");
		}
	}
	release();

	this->m_data = new uint8_t* [this->m_height];
	for (unsigned int i = 0; i < this->m_height; i++) {
		this->m_data[i] = new uint8_t[this->m_width];
	}

	unsigned int pixel;
	unsigned int minValue = 0;
	unsigned int maxValue = 255;

	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			file >> pixel;
			pixel = std::max(minValue, pixel);
			pixel = std::min(maxValue, pixel);
			this->m_data[i][j] = static_cast<unsigned char>(pixel);
		}
	}
	file.close();
	return true;
}

bool Image::save(std::string imagePath) {
	std::ofstream file(imagePath);
	if (!file.is_open()) {
		throw std::invalid_argument("Error: Could not open the file");
		return false;
	}

	file << "P2\n";
	file << this->m_width << ' ' << this->m_height << '\n';
	file << "255\n";

	const int valuesPerLine = 12;
	int current = 0;

	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			file << std::setw(3) << static_cast<unsigned int>(this->m_data[i][j]) << "  ";
			current++;

			if (current >= valuesPerLine) {
				file << '\n';
				current = 0;
			}
		}
	}
	file.close();
	return true;
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
	for (unsigned int i = 0; i < dt.m_height; i++, os<<'\n') {
		for (unsigned int j = 0; j < dt.m_width; j++) {
			os << std::setw(3) << static_cast<unsigned int>(dt.m_data[i][j]) << "  ";
		}
	}
	return os;
}

Image Image::operator+(const Image& image) const {
	if (this->m_width != image.m_width || this->m_height != image.m_height) {
		throw std::invalid_argument("Width and height are not the same");
	}
	
	Image result(this->m_width, this->m_height);
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			int sum = this->m_data[i][j] + image.m_data[i][j];
			result.m_data[i][j] = static_cast<uint8_t>(std::min(sum, 255));
		}
	}
	return result;
}

Image Image::operator-(const Image& image) const {
	if (this->m_width != image.m_width || this->m_height != image.m_height) {
		throw std::invalid_argument("Width and height are not the same");
	}

	Image result(this->m_width, this->m_height);
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			int sum = this->m_data[i][j] - image.m_data[i][j];
			result.m_data[i][j] = static_cast<uint8_t>(std::max(sum, 0));
		}
	}
	return result;
}

Image Image::operator+(int8_t scalar) const {
	Image result(this->m_width, this->m_height);
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			int sum = this->m_data[i][j] + scalar;;
			result.m_data[i][j] = static_cast<uint8_t>(std::max(std::min(sum, 255), 0));
		}
	}
	return result;
}

Image Image::operator-(int8_t scalar) const {
	Image result(this->m_width, this->m_height);
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			int sum = this->m_data[i][j] - scalar;;
			result.m_data[i][j] = static_cast<uint8_t>(std::max(std::min(sum, 255), 0));
		}
	}
	return result;
}

Image Image::operator*(int8_t scalar) const {
	Image result(this->m_width, this->m_height);
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			int sum = this->m_data[i][j] * scalar;;
			result.m_data[i][j] = static_cast<uint8_t>(std::max(std::min(sum, 255), 0));
		}
	}
	return result;
}

bool Image::isEmpty() const {
	return this->m_data == nullptr || this->m_width == 0 || this->m_height == 0;
}

uint8_t& Image::at(unsigned int x, unsigned int y) const {
	if (x >= this->m_height || y >= this->m_width) {
		throw std::invalid_argument("Position out of range");
	}
	return this->m_data[x][y];
}

uint8_t& Image::at(Point pt) const {
	return at(pt.x, pt.y);
}

uint8_t* Image::row(int y) const {
	if (y < 0 || y >= this->m_height) {
		throw std::invalid_argument("Position out of range");
	}
	return this->m_data[y];
}


Image Image::zeros(unsigned int width, unsigned int height) {
	Image image(width, height);
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			image.m_data[i][j] = 0;
		}
	}
	return image;
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image image(width, height);
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			image.m_data[i][j] = 1;
		}
	}
	return image;
}

bool Image::inGrid(unsigned int x, unsigned int y) {
	return x >= 0 && y >= 0 && x < this->m_height && y < this->m_width;
}
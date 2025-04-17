#include "image.h"
#include <fstream>
#include <sstream>

Image::Image() {
	this->m_data = nullptr;
	this->m_width = 0;
	this->m_height = 0;
	this->maxValue = 0;
}

Image::Image(unsigned int w, unsigned int h, unsigned int mV) {
	this->m_width = w;
	this->m_height = h;
	this->maxValue = mV;
	if (this->m_width == 0 || this->m_height == 0) {
		this->m_width = 0;
		this->m_height = 0;
		this->m_data = nullptr;
	}
	else {
		this->m_data = new unsigned char* [this->m_height];
		for (unsigned int i = 0; i < this->m_height; i++) {
			this->m_data[i] = new unsigned char[this->m_width];
		}
	}
}

Image::Image(const Image& other) {
	this->m_width = other.m_width;
	this->m_height = other.m_height;
	this->maxValue = other.maxValue;

	this->m_data = new unsigned char* [this->m_height];
	for (unsigned int i = 0; i < this->m_height; i++) {
		this->m_data[i] = new unsigned char[this->m_width];

		for (unsigned int j = 0; j < this->m_width; j++) {
			this->m_data[i][j] = other.m_data[i][j];
		}
	}
}

Image::~Image() {
	if (this->m_data) {
		for (unsigned int i = 0; i < this->m_height; i++) {
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}
}

Image& Image::operator=(const Image& other) {
	if (this != &other) {
		if (this->m_data) {
			for (unsigned int i = 0; i < this->m_height; i++) {
				delete[] this->m_data[i];
			}
			delete[] this->m_data;
		}

		this->m_width = other.m_width;
		this->m_height = other.m_height;
		this->maxValue = other.maxValue;

		this->m_data = new unsigned char* [this->m_height];
		for (unsigned int i = 0; i < this->m_height; i++) {
			this->m_data[i] = new unsigned char[this->m_width];

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
		std::cerr << "Error: Could not open file " << imagePath << '\n';
		return false;
	}

	std::string line;
	std::string magicNumber;
	unsigned int width = 0, height = 0, maxValue = 0;

	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#')
			continue;

		std::istringstream iss(line);
		iss >> magicNumber;
		
		if (magicNumber == "P2") {
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
				max >> this->maxValue;
				break;
			}
			break;
		}
	}
	if (this->m_data) {
		for (unsigned int i = 0; i < this->m_height; i++) {
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}

	this->m_data = new unsigned char* [this->m_height];
	for (unsigned int i = 0; i < this->m_height; i++) {
		this->m_data[i] = new unsigned char[this->m_width];
	}

	unsigned int pixel;
	for (unsigned int i = 0; i < this->m_height; i++) {
		for (unsigned int j = 0; j < this->m_width; j++) {
			file >> pixel;
			this->m_data[i][j] = static_cast<unsigned char>(pixel);
		}
	}
	return true;
}
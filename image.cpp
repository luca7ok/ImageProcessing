#include "image.h"

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
		this->m_data = new unsigned char* [this->m_width];
		for (unsigned int i = 0; i < this->m_width; i++) {
			this->m_data[i] = new unsigned char[this->m_height];
		}
	}
}

Image::Image(const Image& other) {
	this->m_width = other.m_width;
	this->m_height = other.m_height;

	this->m_data = new unsigned char* [this->m_width];
	for (unsigned int i = 0; i < this->m_width; i++) {
		this->m_data[i] = new unsigned char[this->m_height];

		for (unsigned int j = 0; j < this->m_height; j++) {
			this->m_data[i][j] = other.m_data[i][j];
		}
	}
}

Image::~Image() {
	if (this->m_data) {
		for (unsigned int i = 0; i < this->m_width; i++) {
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}
}

Image& Image::operator=(const Image& other) {
	if (this != &other) {
		if (this->m_data) {
			for (unsigned int i = 0; i < this->m_width; i++) {
				delete[] this->m_data[i];
			}
			delete[] this->m_data;
		}

		this->m_width = other.m_width;
		this->m_height = other.m_height;

		this->m_data = new unsigned char* [this->m_width];
		for (unsigned int i = 0; i < this->m_width; i++) {
			this->m_data[i] = new unsigned char[this->m_height];

			for (unsigned int j = 0; j < this->m_height; j++) {
				this->m_data[i][j] = other.m_data[i][j];
			}
		}
	}
}
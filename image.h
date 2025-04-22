#pragma once
#include <string>
#include "size.h"
#include <iostream>
#include <cstdint>
#include <iomanip>
#include "rectangle.h"

class Image{
private:
	uint8_t** m_data;
	unsigned int m_width;
	unsigned int m_height;
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);
	Image& operator=(const Image& other);

	~Image();

	bool load(std::string imagePath);
	bool save(std::string imagePath);
	
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	Image operator+(const Image& i) const;
	Image operator-(const Image& i) const;
	Image operator+(int8_t scalar) const;
	Image operator-(int8_t scalar) const;
	Image operator*(int8_t scalar) const;

	bool isEmpty() const;
	Size size() const;

	unsigned int width() const;
	unsigned int height() const;
	
	uint8_t& at(unsigned int x, unsigned int y) const;
	uint8_t& at(Point pt) const;
	
	uint8_t* row(int y) const;
	
	void release();
	
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height); 

	bool inGrid(unsigned int x, unsigned int y);
};
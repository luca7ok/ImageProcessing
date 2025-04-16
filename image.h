#pragma once
#include <string>
#include "size.h"

class Image{
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);

	~Image();

	bool load(std::string imagePath);
	bool save(std::string imagePath);

	Image& operator=(const Image& other);
	Image operator+(const Image& i);
	Image operator-(const Image& i);
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);

	bool getROI(Image& roiImg, Rectangle roiRect);
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	bool isEmpty() const;
	Size size() const;

	unsigned int width() const;
	unsigned int height() const;

	unsigned char& at(unsigned int x, unsigned int y);
	unsigned char& at(Point pt);

	unsigned char* row(int y);

	void release();
	
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);
private:
	unsigned char** m_data;
	unsigned int m_width;
	unsigned int m_height;
};
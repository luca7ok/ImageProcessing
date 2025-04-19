#include "rectangle.h"

Rectangle::Rectangle() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rectangle::Rectangle(Point p1, Point p2) {
	this->x = p1.x;
	this->y = p1.y;
	this->width = p2.y - p1.y;
	this->height = p2.x - p1.x;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
	os << rect.x << ' ' << rect.y << ' ' << '\n' << rect.width << ' ' << rect.height << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rect) {
	is >> rect.x >> rect.y >> rect.width >> rect.height;
	return is;
}
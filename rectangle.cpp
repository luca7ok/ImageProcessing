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

Rectangle Rectangle::operator+(const Point& p) const {
	return Rectangle(this->x + p.x, this->y + p.y, this->width, this->height);
}

Rectangle Rectangle::operator-(const Point& p) const {
	return Rectangle(this->x - p.x, this->y - p.y, this->width, this->height);
}

Rectangle Rectangle::operator&(const Rectangle& r) const {
	int x1 = std::max(x, r.x);
	int y1 = std::max(y, r.y);
	int x2 = std::min(x + width, r.x + r.width);
	int y2 = std::min(y + height, r.y + r.height);

	if (x2 <= x1 || y2 <= y1) {
		return Rectangle();
	}
	return Rectangle(x1, y1, x2 - x1, y2 - y1);
}

Rectangle Rectangle::operator|(const Rectangle& r) const {
	if (width == 0 && height == 0) return r;
	if (r.width == 0 && r.height == 0) return *this;

	int x1 = std::min(x, r.x);
	int y1 = std::min(y, r.y);
	int x2 = std::max(x + width, r.x + r.width);
	int y2 = std::max(y + height, r.y + r.height);

	return Rectangle(x1, y1, x2 - x1, y2 - y1);
}
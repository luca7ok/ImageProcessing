#include "point.h"

Point::Point() {
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os << point.x << ' ' << point.y << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
	is >> point.x >> point.y;
	return is;
}
#pragma once
#include "point.h";
#include <algorithm>

class Rectangle {
public:
	int x;
	int y;
	int width;
	int height;

	Rectangle();
	Rectangle(int x, int y, int widht, int height);
	Rectangle(Point p1, Point p2);

	friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);
	friend std::istream& operator>>(std::istream& is, Rectangle& rect);

	Rectangle operator+(const Point& p) const;
	Rectangle operator-(const Point& p) const;
	Rectangle operator&(const Rectangle& r) const;
	Rectangle operator|(const Rectangle& r) const;
};
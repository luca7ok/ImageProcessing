#pragma once
#include <iostream>

class Point {
public:
	int x;
	int y;

	Point();
	Point(int x, int y);

	friend std::ostream& operator<<(std::ostream& os, const Point& point);
	friend std::istream& operator>>(std::istream& os, Point& point);
};
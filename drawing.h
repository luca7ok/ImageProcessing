#pragma once
#include "point.h"
#include "image.h"
#include "rectangle.h"

namespace Drawing {
	void drawCircle(Image& img, Point center, int radius, uint8_t color) {
		// Mid-Point Circle Drawing Algorithm
		
		if (img.isEmpty()) {
			throw std::invalid_argument("Image is empty");
		}
		if (radius <= 0) {
			throw std::invalid_argument("Radius is negative");
		}

		int x = radius;
		int y = 0;
		int err = 0;

		while (x >= 0) {
			if (img.inGrid(center.x + x, center.y + y)) {
				img.at(center.x + x, center.y + y) = color;
			}
			if (img.inGrid(center.x + y, center.y + x)) {
				img.at(center.x + y, center.y + x) = color;
			}
			if (img.inGrid(center.x - y, center.y + x)) {
				img.at(center.x - y, center.y + x) = color;
			}
			if (img.inGrid(center.x - x, center.y + y)) {
				img.at(center.x - x, center.y + y) = color;
			}
			if (img.inGrid(center.x - x, center.y - y)) {
				img.at(center.x - x, center.y - y) = color;
			}
			if (img.inGrid(center.x - y, center.y - x)) {
				img.at(center.x - y, center.y - x) = color;
			}
			if (img.inGrid(center.x + y, center.y - x)) {
				img.at(center.x + y, center.y - x) = color;
			}
			if (img.inGrid(center.x + x, center.y - y)) {
				img.at(center.x + x, center.y - y) = color;
			}

			if (err <= 0) {
				y += 1;
				err += 2 * y + 1;
			}
			if (err > 0) {
				x -= 1;
				err -= 2 * x + 1;
			}
		}
	}
	
	void drawLine(Image& img, Point p1, Point p2, uint8_t color) {
		// Bresenham’s Line Drawing Algorithm

		if (img.isEmpty()) {
			throw std::invalid_argument("Image is empty");
		}

		int dx = abs(p2.x - p1.x);
		int dy = abs(p2.y - p1.y);

		int sx = (p1.x < p2.x) ? 1 : -1;
		int sy = (p1.y < p2.y) ? 1 : -1;

		int err = (dx > dy ? dx : -dy) / 2;
		int err2;

		while (true) {
			if (img.inGrid(p1.x, p1.y)) {
				img.at(p1.x, p1.y) = color;
			}

			if (p1.x == p2.x && p1.y == p2.y) break;

			err2 = err;
			if (err2 > -dx) {
				err -= dy;
				p1.x += sx;
			}
			if (err2 < dy) {
				err += dx;
				p1.y += sy;
			}
		}
	}

	void drawRectangle(Image& img, Rectangle r, uint8_t color) {
		if (img.isEmpty()) {
			throw std::invalid_argument("Image is empty");
		}
		int x1 = r.x;
		int y1 = r.y;
		int x2 = r.x + r.height;
		int y2 = r.y + r.width;

		drawLine(img, Point(x1, y1), Point(x2, y1), color);
		drawLine(img, Point(x2, y1), Point(x2, y2), color);
		drawLine(img, Point(x1, y2), Point(x2, y2), color);
		drawLine(img, Point(x1, y1), Point(x1, y2), color);
	}

	void drawRectangle(Image& img, Point tl, Point br, uint8_t color) {
		if (img.isEmpty()) {
			throw std::invalid_argument("Image is empty");
		}

		drawRectangle(img, Rectangle(tl, br), color);
	}
}
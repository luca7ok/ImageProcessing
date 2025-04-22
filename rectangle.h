#pragma once
#include "point.h";
#include <algorithm>

/**
* @class Rectangle
* @brief Represents a 2D axis-aligned rectangle with integer coordinates
*/
class Rectangle {
public:
	int x;		///< Left coordinate of the rectangle
	int y;		///< Top coordinate of the rectangle
	int width;	///< Width of the rectangle (must be >= 0)
	int height;	///< Height of the rectangle (must be >= 0)

	/**
	* @brief Default constructor. Creates an empty rectangle at (0,0).
	*/
	Rectangle();

	/**
	* @brief Constructor. Creates a rectangle from position and dimensions
	* @param x Left coordinate
	* @param y Top coordinate
	* @param width Width (must be >= 0)
	* @param height Height (must be >= 0)
	*/
	Rectangle(int x, int y, int widht, int height);

	/**
	* @brief Constructor. Creates a rectangle from two corner points
	* @param p1 First corner (top-left)
	* @param p2 Second corner (bottom-right)
	*/
	Rectangle(Point p1, Point p2);

	/**
	* @brief Outputs rectangle as "x y width height"
	* @param os Output stream
	* @param rect Rectangle to output
	* @return Reference to the output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

	/**
	* @brief Reads rectangle from "x y width height" format
	* @param is Input stream
	* @param rect Rectangle to populate
	* @return Reference to the input stream
	*/
	friend std::istream& operator>>(std::istream& is, Rectangle& rect);

	/**
	* @brief Translates the rectangle by a point's coordinates
	* @param p Point containing translation offsets
	* @return New translated rectangle
	*/
	Rectangle operator+(const Point& p) const;

	/**
	* @brief Translates the rectangle inversely by a point's coordinates
	* @param p Point containing translation offsets
	* @return New translated rectangle
	*/
	Rectangle operator-(const Point& p) const;

	/**
	* @brief Computes intersection of two rectangles
	* @param r Rectangle to intersect with
	* @return Intersection rectangle
	*/
	Rectangle operator&(const Rectangle& r) const;

	/**
	* @brief Computes union bounding box of two rectangles
	* @param r Rectangle to unite with
	* @return Minimal rectangle containing both inputs
	*/
	Rectangle operator|(const Rectangle& r) const;
};
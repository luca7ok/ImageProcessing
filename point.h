#pragma once
#include <iostream>


/**
* @class Point
* @brief Represents a 2D point with integer coordinates
*/
class Point {
public:
	int x;	///< X-coordinate
	int y;	///< Y-coordinate

	/**
	* @brief Default constructor. Creates a point at (0, 0).
	*/
	Point();

	/**
	* @brief Constructs a point with specified coordinates
	* @param x X-coordinate
	* @param y Y-coordinate
	*/
	Point(int x, int y);

	/**
	* @brief Outputs the point as "(x, y)" to a stream
	* @param os Output stream 
	* @param point Point to output
	* @return Reference to the output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, const Point& point);

	/**
	* @brief Reads a point from a stream in "x y" format
	* @param is Input stream
	* @param point Point to store the result
	* @return Reference to the input stream
	*/
	friend std::istream& operator>>(std::istream& os, Point& point);
};
#pragma once

/**
* @class Size
* @brief Represents the dimensions (width and height) of a 2D object
*/
class Size {
private:
	unsigned int width;		///< The width dimension (must be >= 0)
	unsigned int height;	///< The height dimension (must be >= 0)
public:
    /**
    * @brief Constructor. Creates a Size object with given dimensions
    * @param w Width of the object (default: 0).
    * @param h Height of the object (default: 0).
    */
	Size(unsigned int w = 0, unsigned int h = 0) : width{ w }, height{ h } {};
};
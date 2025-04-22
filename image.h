#pragma once
#include <string>
#include "size.h"
#include <iostream>
#include <cstdint>
#include <iomanip>
#include "rectangle.h"

/**
* @class Image
* @brief Represents a grayscale image
*/
class Image{
private:
	uint8_t** m_data;		///< 2D array of pixel data
	unsigned int m_width;	///< Width of the image (must be >= 0)
	unsigned int m_height;	///< Height of the image ( must be >= 0)
public:
	/**
	* @brief Default constructor. Creates empty image
	*/
	Image();

	/**
	* @brief Constructor. Creates a blank image of specified size
	* @param w Width of the image (must be >= 0)
	* @param h Height of the image (must be >= 0)
	*/
	Image(unsigned int w, unsigned int h);

	/**
	* @brief Deep-copy constructor
	* @param Other Image to copy from
	*/
	Image(const Image& other);

	/**
	* @brief Copy asignment operator. Makes a deep-copy of 'other'
	* @param other Image to copy from
	* @return Reference to this object
	*/
	Image& operator=(const Image& other);

	/**
	* @brief Destructor. Calls release()
	*/
	~Image();

	/**
	* @brief Loads a grayscale image from a PGM (P2/P5) file
	* @param imagePath Input file path
	* @return 'true' if successful, 'false' otherwise
	*/
	bool load(std::string imagePath);

	/**
	* @brief Saves the image to a PGM file
	* @param imagePath output file path
	* @return 'true' if successful, 'false' otherwise
	*/
	bool save(std::string imagePath);
	
	/**
	* @brief Outputs the image as ASCII to a stream
	* @param os Output stream 
	* @param dt Image to display
	* @return Reference to the output stream.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);

	/**
	* @brief Adds two images pixel-wise
	* @param i Image to add
	* @return New image containing the result
	*/
	Image operator+(const Image& i) const;

	/**
	* @brief Subtracts two images pixel-wise
	* @param i Image to subtract
	* @return New image containing the result
	*/
	Image operator-(const Image& i) const;

	/**
	* @brief Adds a scalar to every pixel
	* @param scalar Value to add
	* @return New image containing the result
	*/
	Image operator+(int8_t scalar) const;

	/**
	* @brief Subtracts a scalar from every pixel
	* @param scalar Value to subtract
	* @return New image containing the result
	*/
	Image operator-(int8_t scalar) const;

	/**
	* @brief Multiplies every pixel by a scalar
	* @param scalar Value to multiply by
	* @return New image containing the result
	*/
	Image operator*(int8_t scalar) const;

	/**
	* @brief Checks if the image is empty (no allocated data)
	* @return `true` if `m_data == nullptr` or dimensions are 0, 'false' otherwise
	*/
	bool isEmpty() const;

	/**
	* @brief Returns the image dimensions as a `Size` object
	* @return `Size(m_width, m_height)`
	*/
	Size size() const;

	/**
	* @brief Gets the image width
	* @return Value of `m_width`
	*/
	unsigned int width() const;

	/**
	* @brief Gets the image height
	* @return Value of `m_height`
	*/
	unsigned int height() const;
	
	/**
	* @brief Accesses a pixel at (x, y)
	* @param x Row index 
	* @param y Column index
	* @return Reference to the pixel
	*/
	uint8_t& at(unsigned int x, unsigned int y) const;

	/**
	* @brief Accesses a pixel at `(pt.x, pt.y)`
	* @param pt Point containing (x, y) coordinates
	* @return Reference to the pixel 
	*/
	uint8_t& at(Point pt) const;
	
	/**
	* @brief Gets a pointer to the start of a row
	* @param y Row index
	* @return Pointer to row `y`
	*/
	uint8_t* row(int y) const;
	
	/**
	* @brief Frees allocated pixel data
	*/
	void release();
	
	/**
	* @brief Creates a black image (all zeros) of given size
	* @param width Width of the new image
	* @param height Height of the new image 
	* @return New `Image` filled with zeros
	*/
	static Image zeros(unsigned int width, unsigned int height);

	/**
	* @brief Creates a white image (all ones) of given size
	* @param width Width of the new image
	* @param height Height of the new image
	* @return New `Image` filled with ones
	*/
	static Image ones(unsigned int width, unsigned int height); 

	/**
	* @brief Checks if (x, y) is a valid pixel coordinate
	* @param x Row index
	* @param y Column index
	* @return `true` if (x, y) is within bounds, `false` otherwise
	*/
	bool inGrid(unsigned int x, unsigned int y);
};
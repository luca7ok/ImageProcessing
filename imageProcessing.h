#pragma once
#include "image.h"

/**
* @class ImageProcessing
* @brief Abstract base class for image processing operations
* @details Derived classes must implement the `process()` method to apply
*          specific transformations to images
*/
class ImageProcessing {
public:
    /**
    * @brief Pure virtual function to process an input image and store the result
    * @param src Input image (source) to be processed
    * @param dst Output image (destination) where the result is stored
    */
	virtual void process(const Image& src, Image& dst) = 0;

};
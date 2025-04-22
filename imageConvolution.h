#pragma once
#include "imageProcessing.h"
#define MAX_SIZE 3		///< Maximum kernel size supported

/**
* @class ImageConvolution
* @brief Applies kernel-based convolution to images with configurable scaling
* @details Supports arbitrary odd-sized kernels 
*          - Kernel matrix application
*          - Custom post-processing scaling function
*/
class ImageConvolution : public ImageProcessing{
private:
	int kernelWidth;					///< Width of the convolution kernel (must be odd)
	int kernelHeight;					///< Height of the convolution kernel (must be odd)
	int8_t** kernel;					///< 2D kernel matrix
	float (*scalingFunction)(float);	///< Post-convolution scaling callback
public:
	/**
	* @brief Constructor. Creates a convolver with specified kernel and scaling function
	* @param kW Kernel width (must be odd and <= MAX_SIZE).
	* @param kH Kernel height (must be odd and <= MAX_SIZE).
	* @param k Kernel matrix
	* @param sF Scaling function to normalize results
	*/
	ImageConvolution(int kW, int kH, const int k[][MAX_SIZE], float (*sF)(float));

	/**
	* @brief Applies convolution to an image
	* @param src Input image (must be non-empty).
	* @param dst Output image (resized if dimensions mismatch)
	*/
	void process(const Image& src, Image& dst) override;

	/**
	* @brief Destructor. Frees allocated kernel memory
	*/
	~ImageConvolution();

};
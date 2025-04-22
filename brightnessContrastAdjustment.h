#pragma once
#include "imageProcessing.h"

/**
* @class BrightnessContrastAdjustment
* @brief Adjusts image brightness and contrast using linear transformation
* @details Applies the formula: `output = alpha * input + beta`, where:
*          - `alpha` controls contrast (1.0 = no change, <1.0 = reduced contrast, >1.0 = increased contrast)
*          - `beta` controls brightness (0 = no change, positive = brighter, negative = darker)
*/
class BrightnessContrastAdjustment : public ImageProcessing {
private:
	float alpha;	///< Contrast multiplier (default: 1.0)
	float beta;		///< Brightness offset (default: 0.0)
public:
	/**
	* @brief Constructs a brightness/contrast adjuster
	* @param alpha Contrast multiplier
	* @param beta Brightness offset
	*/
	BrightnessContrastAdjustment(float alpha = 1.0f, float beta = 0.0f);

	/**
	 * @brief Applies brightness/contrast adjustment to an image
	 * @param src Input image (must be non-empty)
	 * @param dst Output image (resized if dimensions mismatch)
	 */
	void process(const Image& src, Image& dst) override;
};
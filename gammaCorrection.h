#pragma once
#include "imageProcessing.h"

/**
 * @class GammaCorrection
 * @brief Applies gamma correction to an image
 * @details Performs the operation: `output = 255 * (input/255)^gamma`
 *          - Gamma < 1.0: Brightens dark regions (e.g., gamma=0.5)
 *          - Gamma = 1.0: No change
 *          - Gamma > 1.0: Darkens bright regions (e.g., gamma=2.0)
 */
class GammaCorrection : public ImageProcessing{
private:
	float gamma;	///< Gamma exponent (must be > 0, default: 1.0)
public:
	/**
	* @brief Constructor. Creates a gamma corrector with specified exponent
	* @param g Gamma value
	*/
	GammaCorrection(float g = 1.0f);

	/**
	* @brief Applies gamma correction to an image
	* @param src Input image (must be non-empty)
	* @param dst Output image (resized if dimensions mismatch).
	*/
	void process(const Image& src, Image& dst) override;
};
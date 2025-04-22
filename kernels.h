#pragma once


/**
 * @struct identity
 * @brief Identity kernel (no modification to image)
 * @note Output = Original pixel value (scale function returns input unchanged)
 */
struct identity {
	static constexpr int kernel[3][3] = {
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 0}
	};
	static float scale(float value) {
		return value;
	}
};

/**
 * @struct gaussianBlur
 * @brief 3x3 Gaussian blur kernel
 * @note Provides smooth blur while preserving edges better than mean blur
 */
struct gaussianBlur {
	static constexpr int kernel[3][3] = {
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1}
	};
	static float scale(float value) {
		return value / 16.0f;
	}
};


/**
 * @struct meanBlur
 * @brief 3x3 box blur
 * @note Uniform blur that may cause edge softening
 */
struct meanBlur {
	static constexpr int kernel[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};
	static float scale(float value) {
		return value / 9.0f;
	}

};

/**
 * @struct horizontalSobel
 * @brief Horizontal edge detection kernel (Sobel operator)
 * @note Detects vertical edges by measuring horizontal intensity changes
 *       Scale function remaps output to [0, 255] range
 */
struct horizontalSobel {
	static constexpr int kernel[3][3] = {
		{1, 2, 1},
		{0, 0, 0},
		{-1, -2, -1}
	};
	static float scale(float value) {
		const float minInput = -4.0f * 255.0f;
		const float maxInput = 4.0f * 255.0f;
		return (value - minInput) * 255.0f / (maxInput - minInput);
	}
};

/**
 * @struct verticalSobel
 * @brief Vertical edge detection kernel (Sobel operator)
 * @note Detects horizontal edges by measuring vertical intensity changes
 *       Scale function remaps output to [0, 255] range
 */
struct verticalSobel {
	static constexpr int kernel[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	static float scale(float value) {
		const float minInput = -4.0f * 255.0f;
		const float maxInput = 4.0f * 255.0f;
		return (value - minInput) * 255.0f / (maxInput - minInput);
	}
};
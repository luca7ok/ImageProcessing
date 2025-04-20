#pragma once

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
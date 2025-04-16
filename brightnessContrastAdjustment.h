#pragma once
#include "imageProcessing.h"

class BrightnessContrastAdjustment : public ImageProcessing {
private:
	float alpha;
	float beta;
public:
	BrightnessContrastAdjustment(float alpha = 1.0f, float beta = 0.0f);

	void process(const Image& src, Image& dst) override;
};
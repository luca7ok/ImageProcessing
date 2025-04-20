#pragma once
#include "imageProcessing.h"

class GammaCorrection : public ImageProcessing{
private:
	float gamma;
public:
	GammaCorrection(float g = 1.0f);

	void process(const Image& src, Image& dst) override;
};
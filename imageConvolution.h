#pragma once
#include "imageProcessing.h"
#define MAX_WIDTH 3

class ImageConvolution : public ImageProcessing{
private:
	int kernelWidth;
	int kernelHeight;
	int8_t** kernel;
	float (*scalingFunction)(float);
public:
	ImageConvolution(int kW, int kH, const int k[][MAX_WIDTH], float (*sF)(float));

	void process(const Image& src, Image& dst) override;

	~ImageConvolution();

};
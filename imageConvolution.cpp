#include "imageConvolution.h"

ImageConvolution::ImageConvolution(int kW, int kH, const int k[][MAX_WIDTH], float (*sF)(float)) {
	if (kW %2 == 0 || kH % 2 == 0) {
		throw std::invalid_argument("Kernal dimensions must be odd");
	}
	this->kernelWidth = kW;
	this->kernelHeight = kH;
	this->scalingFunction = sF;
	this->kernel = new int8_t * [this->kernelHeight];
	for (int i = 0; i < this->kernelHeight; i++) {
		this->kernel[i] = new int8_t[this->kernelWidth];
		for (int j = 0; j < this->kernelWidth; j++) {
			this->kernel[i][j] = k[i][j];
		}
	}
}

ImageConvolution::~ImageConvolution() {
	if (this->kernel) {
		for (unsigned int i = 0; i < this->kernelHeight; i++) {
			delete[] this->kernel[i];
		}
		delete[] this->kernel;
	}
}

void ImageConvolution::process(const Image& src, Image& dst) {
	if (src.isEmpty()) {
		throw std::invalid_argument("Source image is empty");
	}

	if (dst.width() != src.width() || dst.height() != src.height()) {
		dst = Image(src.width(), src.height());
	}

	const int kernelCenterX = this->kernelHeight / 2;
	const int kernelCenterY = this->kernelWidth / 2;

	for (unsigned int i = 0; i < src.height(); i++) {
		for (unsigned int j = 0; j < src.width(); j++) {
			float result = 0.0f;

			for (int kx = 0; kx < this->kernelHeight; kx++) {
				for (int ky = 0; ky < this->kernelWidth; ky++) {
					int imgX = i - kx + kernelCenterX;
					int imgY = j - ky + kernelCenterY;

					if (imgX < 0) imgX = 0;
					if (imgY < 0) imgY = 0;
					if (imgX >= src.height()) imgX = src.height() - 1;
					if (imgY >= src.width()) imgY = src.width() - 1;

					result = result + kernel[kx][ky] * src.at(imgX, imgY);

				}
			}
			result = this->scalingFunction(result);
			result = std::max(0.0f, std::min(255.0f, result));
			dst.at(i, j) = static_cast<uint8_t>(result);
		}
	}
}
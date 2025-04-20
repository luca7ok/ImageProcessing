#include "gammaCorrection.h"

GammaCorrection::GammaCorrection(float g) {
	this->gamma = g;
}

void GammaCorrection::process(const Image& src, Image& dst) {
	if (src.isEmpty()) {
		throw std::invalid_argument("Source image is empty");
	}

	if (dst.width() != src.width() || dst.height() != src.height()) {
		dst = Image(src.width(), src.height());
	}

	for (unsigned int i = 0; i < src.height(); i++) {
		for (unsigned int j = 0; j < src.width(); j++) {
			float pixel = static_cast<float>(src.at(i, j));
			pixel = std::pow(pixel, this->gamma);
			pixel = std::max(0.0f, std::min(255.0f, pixel));

			dst.at(i, j) = static_cast<uint8_t>(pixel);
		}
	}
}
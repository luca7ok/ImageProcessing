#define _CRT_DBG_MALLOC
#include "image.h"
#include "brightnessContrastAdjustment.h"
#include "gammaCorrection.h"
#include "imageConvolution.h"
#include "kernels.h"


int main() {
	try {
		Image image1, image2;
		image1.load("inputImages/casablanca.ascii.pgm");
		ImageConvolution conv(3, 3, horizontalSobel::kernel, horizontalSobel::scale);
		conv.process(image1, image1);
		image1.save("output.ascii.pgm");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	_CrtDumpMemoryLeaks();

	return 0;
}
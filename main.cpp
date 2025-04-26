#define _CRT_DBG_MALLOC
#include "image.h"
#include "brightnessContrastAdjustment.h"
#include "gammaCorrection.h"
#include "imageConvolution.h"
#include "kernels.h"
#include "tests.h"
#include <filesystem>

int main() {
	try {
		testAll();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	_CrtDumpMemoryLeaks();

	return 0;
}
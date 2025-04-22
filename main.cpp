#define _CRT_DBG_MALLOC
#include "image.h"
#include "brightnessContrastAdjustment.h"
#include "gammaCorrection.h"
#include "imageConvolution.h"
#include "kernels.h"
#include "drawing.h"
#include <filesystem>

int main() {
	try {
		/*for (const auto& entry : std::filesystem::directory_iterator("inputImages")){
			std::cout<<entry.path().filename().string()<<'\n';
		}*/
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	_CrtDumpMemoryLeaks();

	return 0;
}
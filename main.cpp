#include "image.h"

int main() {
	
	Image image;
	image.load("inputImages/coins.ascii.pgm");
	image.save("output.ascii.pgm");
	return 0;
}
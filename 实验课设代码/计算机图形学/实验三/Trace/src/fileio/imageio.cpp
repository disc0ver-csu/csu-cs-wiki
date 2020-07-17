//#define cimg_use_png
//#define cimg_use_jpeg

#include "CImg.h"
#include "imageio.h"

using namespace cimg_library;

unsigned char * load(const char * filename, int &width, int &height)
{
	CImg<unsigned char> image (filename);
	width = (int)image.width;
	height = (int)image.height;
	unsigned char * data = new unsigned char [(int)image.width * (int)image.height * 3]; 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width ; x++) {
			for (int rgb = 0; rgb < 3; rgb++) {
				data[(height-1-y)*3*width + 3*x + rgb] = image.data[rgb*width*height + y*width + x];
			}
		}
	}
	return data;
}

void save(const char * filename, const unsigned char * imageBuffer, int width, int height, const char * type, int quality)
{
	unsigned char * shuffled = new unsigned char[3 * width * height];
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width ; x++) {
			for (int rgb = 0; rgb < 3; rgb++) {
				shuffled[rgb*width*height + y*width + x ] = imageBuffer[(height-1-y)*3*width + 3*x + rgb];
			}
		}
	}
	CImg<unsigned char> image (shuffled, width, height, 1, 3, false);
	if (!strcmp(type, ".jpg"))
		image.save_jpeg(filename, quality);
	else if (!strcmp(type, ".png"))
		image.save_png(filename);
	delete[] shuffled;
}

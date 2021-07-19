#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name: Saud Hashmi
Email: en19cs303046@medicaps.ac.in

(...end multi-line comment.)
******************** */

using namespace std;
using uiuc::PNG;
using uiuc::HSLAPixel;

PNG grayscale(PNG image) {
	for (unsigned x = 0; x < image.width(); x++) {
		for (unsigned y = 0; y < image.height(); y++) {
			HSLAPixel & pixel = image.getPixel(x, y);
			pixel.s = 0;
		}
	}

	return image;
}


PNG createSpotlight(PNG image, int centerX, int centerY) {
	double eucDist;
	for (unsigned x = 0; x < image.width(); ++x) {
		for (unsigned y = 0; y < image.height(); ++y) {
			HSLAPixel &pixel = image.getPixel(x, y);
			eucDist = sqrt( (centerX - x) * (centerX - x) + (centerY - y) * (centerY - y) );
			pixel.l = pixel.l - (0.005 * eucDist * pixel.l);
		}
	}
	return image;
}

PNG illinify(PNG image) {
	for (unsigned x = 0; x < image.width(); x++) { 
		for (unsigned y = 0; y < image.height(); y++) {
			HSLAPixel &pixel = image.getPixel(x,y);
			if (pixel.h <= 113.5 || pixel.h >= 293.5) 
				pixel.h = 11;  
			else
				pixel.h = 216;                    
		}
	}
	return image;
}

PNG watermark(PNG firstImage, PNG secondImage) {
	for (unsigned x = 0; x < secondImage.width(); ++x) {
		for (unsigned y = 0; y < secondImage.height(); ++y) {
			HSLAPixel &pixel1 = firstImage.getPixel(x, y);
			HSLAPixel &pixel2 = secondImage.getPixel(x, y);
			if (pixel2.l == 1) 
				pixel1.l += 0.2;
		}
	}
	return firstImage;
}

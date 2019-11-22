#include "filters.h"

filters::filters()
{
}

filters::filters(int widthOrig, int heightOrig, QVector<unsigned char> oData)
{
	width = widthOrig;
	height = heightOrig;
	origData = oData;
}

filters::~filters() {
}

void filters::histogram() {
		//vynulovanie histogrramu

	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++) {
		hist[int(data[i])]++;
	}

	// for (int i = 0; i < 256; i++)
	//	std::cout << "farba: " << i << "hodnota: " << hist[i] << std::endl;
}

void filters::otsuFilter() {

	int total = width*height;

	float sum = 0;
	for (int t = 0; t < 256; t++)
		sum += t * hist[t];

	float sumB = 0;
	int wB = 0;
	int wF = 0;

	float varMax = 0;
	float threshold = 0;

	for (int t = 0; t < 256; t++) {
		wB += hist[t];               // Weight Background
		if (wB == 0) continue;

		wF = total - wB;                 // Weight Foreground
		if (wF == 0) break;

		sumB += (float)(t * hist[t]);

		float mB = sumB / wB;            // Mean Background
		float mF = (sum - sumB) / wF;    // Mean Foreground

		// Calculate Between Class Variance
		float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

		// Check if new maximum found
		if (varBetween > varMax) {
			varMax = varBetween;
			threshold = t;
		}
	}

	std::cout << "treshold: " << threshold << std::endl;
}
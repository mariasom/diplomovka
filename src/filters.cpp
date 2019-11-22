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
	origData.clear();
}

void filters::histogram() {
		//vynulovanie histogrramu

	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++) {
		hist[int(origData[i])]++;
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
	
	newData = origData;
	for (int j = 0; j < width; j++) //vytvorenie dat
		for (int i = 0; i < height; i++)
			if ((int)origData[j * width + i] < threshold)
				newData[j * width + i] = (unsigned char)0;
			else
				newData[j * width + i] = (unsigned char)207;

	for (int j = 0; j < width-1; j++) //vytvorenie hranicnej krivky
		for (int i = 0; i < height-1; i++)
			if ((newData[j * width + i] == 0) && 
				(newData[j * width + (i + 1)] == 207 || newData[j * width + (i - 1)] == 207 || newData[(j + 1) * width + i] == 207 || newData[(j - 1) * width + i] == 207))
				newData[j * width + i] = (unsigned char)255;

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++)
			std::cout << (int)newData[j * width + i] << " ";
		std::cout << std::endl;
	}
}
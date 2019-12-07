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
	hist.resize(256);

	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++) {
		hist[int(origData[i])]++;
	}

	for (int i = 0; i < 256; i++)
		std::cout << "farba: " << i << "hodnota: " << hist[i] << std::endl;
}

void filters::coOcMatrix() {
	//QVector<QVector<int>> t(256);
	t.resize(256);
	for (int i = 0; i < 256; i++) { //cooccurance matrix
		t[i].resize(256);
		for (int j = 0; j < 256; j++) {
			t[i][j] = 0;
			//std::cout << t[i][j] << " ";
		}
		//std::cout << std::endl;
	}



	for (int i = 0; i < 256; i++) { //cooccurance matrix
		t[i].resize(256);
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < width; k++) {// pixels of img
				for (int l = 0; l < height; l++) {
					int tmp = 0;
					if (((int)origData[k * width + l] == i && (int)origData[(k + 1) * width + l] == j) ||
						((int)origData[k * width + l] == i && (int)origData[(k)* width + (l + 1)] == j))
						tmp = 1;
					else
						tmp = 0;

					t[i][j] += tmp;
				}
			}
			//std::cout << t[i][j] << " ";
		}
		//std::cout << std::endl;
	}
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
		wB += hist[t];               // Weight Background (probability distribution)
		if (wB == 0) 
			continue;

		wF = total - wB;                 // Weight Foreground (probability distribution)
		if (wF == 0) 
			break;

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

	/*for (int j = 0; j < width-1; j++) //vytvorenie hranicnej krivky
		for (int i = 0; i < height-1; i++)
			if ((newData[j * width + i] == 0) && 
				(newData[j * width + (i + 1)] == 207 || newData[j * width + (i - 1)] == 207 || newData[(j + 1) * width + i] == 207 || newData[(j - 1) * width + i] == 207))
				newData[j * width + i] = (unsigned char)255;

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++)
			std::cout << (int)newData[j * width + i] << " ";
		std::cout << std::endl;
	}*/
}

/*void filters::kapuraFilter() {

	coOcMatrix();

	int total = width * height;

	float sum = 0;
	for (int t = 0; t < 256; t++)
		sum += t * hist[t];

	float sumD=0 ,sumB = 0, sumA = 0, sumC = 0;
	int pA = 0;
	int pB = 0;
	int pC = 0;
	int pD = 0;
	int wF = 0;

	float varMax = 0;
	float threshold = 0;
	float th = 0;
	int L = 256; //max intensity

	for (int j = 0; j < 256; j++) {
		for (int i = 0; i < 256; i++) {
			pA += t[i][j];   // Weight Background (probability distribution)
			std::cout << "pA:" << pA << std::endl;
			if (pA == 0)
				continue;


			pB += t[i][L - 1 - j];
			pC += t[L - 1 - i][L - 1 - j];
			pD += t[L - 1 - i][j];
			if (pB == 0 || pC == 0 || pD == 0)
				continue;

			if ((L - i - 1) == 0 || (L - j - 1) == 0)
				break;

			float qA = (pA)/(i + 1)*(j + 1);
			float qB = (pB)/ (L - i) * (j + 1);
			float qC = (pC)/ (L - i)*(L - j );
			float qD = (pD)/ (i + 1)*(L - j);

			sumA += pA * (log(pA)-log(qA));
			sumB += pB * (log(pB)-log(qB));
			sumC += pC * (log(pC)-log(qC));
			//std::cout << "hodnota sumB: " << sumB << std::endl;
			sumD += pD * (log(pD)-log(qD));
			//std::cout << "hodnota sumD: " << sumD << std::endl;

			float h = (sumB + sumD + sumA + sumC);

			std::cout << "hodnota h: " << h << std::endl;
			//std::cout << "hodnota ln: " << qLn((sum - sumB) / wF) << std::endl;

			//std::cout << "eb: " << eB << std::endl;
			//std::cout << "ef: " << eF << std::endl;
			//std::cout << "sum of entropies: " <<  eB + eF << std::endl;

			if ((h) < varMax) {
				varMax = h;
				threshold = t[i][j];
			}
		}

		if (pA == 0)
			continue;
	}

	std::cout << "treshold: " << threshold << std::endl;

	newData = origData;
	for (int j = 0; j < width; j++) //vytvorenie dat
		for (int i = 0; i < height; i++)
			if ((int)origData[j * width + i] < threshold)
				newData[j * width + i] = (unsigned char)0;
			else
				newData[j * width + i] = (unsigned char)207;

	/*for (int j = 0; j < width - 1; j++) //vytvorenie hranicnej krivky
		for (int i = 0; i < height - 1; i++)
			if ((newData[j * width + i] == 0) &&
				(newData[j * width + (i + 1)] == 207 || newData[j * width + (i - 1)] == 207 || newData[(j + 1) * width + i] == 207 || newData[(j - 1) * width + i] == 207))
				newData[j * width + i] = (unsigned char)255;*/

	//for (int j = 0; j < width; j++) {
	//	for (int i = 0; i < height; i++)
	//		std::cout << (int)newData[j * width + i] << " ";
	//	std::cout << std::endl;
	//}

//}

void filters::kapuraFilter() { 
	QVector<QVector<float>> S;
	int K = 256;
	QVector<float> histN;
	histN.resize(hist.size());
	for (int i = 0; i < hist.size(); i++) {
		histN[i] = (float)hist[i] / (float)(height*width);
		std::cout << "Normalize hist: " << histN[i] << std::endl;
	}
		
	S = makeTables(K, histN);
	
	float p0 = 0;
	float p1 = 0;
	int qmax = -1;
	int Hmax = -100000;

	for (int q = 0; q < K - 2; q++) {
		p0 = p0 + histN[q];
		std::cout << "p0: " << p0 << std::endl;
		p1 = 1 - p0;
		std::cout << "p1: " << p1 << std::endl;
		float h0 = 0, h1 = 0, h = 0;
		if (p0 > 0) {
			h0 = -(1. / p0)*S[0][q] + log(p0);
			//std::cout << "h0: " << -(1. / p0)*S[0][q] + log(p0) << std::endl;
		}
		else
			h0 = 0;

		if (p1 > 0) {
			h1 = -(1. / p1)*S[1][q] + log(p1);
			//std::cout << "h1: " << -(1. / p1)*S[1][q] + log(p1) << std::endl;
		}
		else
			h1 = 0;

		std::cout << "h0: " << h0 + h1 << std::endl;
		h = h0 + h1; 

		std::cout << "h: " << h << std::endl;
		if (h > Hmax) {
			std::cout << "tu" << std::endl;
			Hmax = h;
			qmax = q;
		}
		std::cout << "treshold: " << qmax << std::endl;

	}

	

	newData = origData;
	for (int j = 0; j < width; j++) //vytvorenie dat
		for (int i = 0; i < height; i++)
			if ((int)origData[j * width + i] < qmax)
				newData[j * width + i] = (unsigned char)0;
			else
				newData[j * width + i] = (unsigned char)207;
}

QVector<QVector<float>> filters::makeTables(int K, QVector<float> histN) {

	QVector<float> S0(K - 1);
	QVector<float> S1(K - 1);

	float s0 = 0, s1 = 0;

	for (int i = 0; i < K; i++) {
		if (histN[i] > 0)
			s0 = s0 + histN[i] * log(histN[i]);
		S0[i] = s0;
		std::cout << "S0[i]: " << S0[i] << std::endl;
	}
	
	for (int i = K; i > 0; i--) {
		S1[i] = s1;
		if (histN[i] > 0)
			s1 = s1 + histN[i] * log(histN[i]);
		std::cout << "S1[i]: " << S1[i] << std::endl;
	}
	return {S0, S1};
}
#include "filters.h"

filters::filters()
{
}

filters::filters(int widthOrig, int heightOrig, QVector<unsigned char> oData)
{
	width = widthOrig;
	height = heightOrig;
	origData = dataToDouble(oData);
	histogram(origData);
}

QVector<double> filters::dataToDouble(QVector<unsigned char> oData) {
	QVector<double> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			tmp[j * width + i] = oData.at(j * width + i);
		}
	}
	return tmp;
}

QVector<int> filters::dataToInt(QVector<unsigned char> oData) {
	QVector<int> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			tmp[j * width + i] = oData.at(j * width + i);
		}
	}
	return tmp;
}

QVector<int> filters::dataToInt(QVector<double> oData) {
	QVector<int> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			tmp[j * width + i] = oData.at(j * width + i);
		}
	}
	return tmp;
}

QVector<unsigned char> filters::dataToChar(QVector<double> data) {
	QVector<unsigned char> tmp;

	tmp.reserve(data.size());
	std::copy(data.cbegin(), data.cend(), std::back_inserter(tmp));

	return tmp;
}

filters::~filters() {
	origData.clear();
}

void filters::histogram(QVector<double> data) {
		//vynulovanie histogrramu
	hist.resize(256);

	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++) {
		hist[int(data[i])]++;
	}

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

int filters::otsuFilter() {

	int total = width*height;

	float sum = 0;
	for (int t = 0; t < 256; t++)
		sum += t * hist[t];

	float sumB = 0;
	int wB = 0;
	int wF = 0;

	float varMax = 0;

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

	return threshold;
	//createNewData();
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

int filters::kapuraFilter() { 
	QVector<QVector<float>> S;
	int K = 256;
	QVector<float> histN;
	histN.resize(hist.size());
	for (int i = 0; i < hist.size(); i++) {
		histN[i] = (float)hist[i] / (float)(height*width);
	}
		
	S = makeTables(K, histN);
	
	float p0 = 0;
	float p1 = 0;
	//int qmax = -1;
	int Hmax = -100000;
	threshold = -1;

	for (int q = 0; q < K - 2; q++) {
		p0 = p0 + histN[q];
		p1 = 1 - p0;
		float h0 = 0, h1 = 0, h = 0;
		if (p0 > 0) {
			h0 = -(1. / p0)*S[0][q] + log(p0);
		}
		else
			h0 = 0;

		if (p1 > 0) {
			h1 = -(1. / p1)*S[1][q] + log(p1);
		}
		else
			h1 = 0;
		h = h0 + h1; 

		if (h > Hmax) {
			Hmax = h;
			threshold = q;
		}
	}
	std::cout << "treshold: " << threshold << std::endl;
	//createNewData();
	return threshold;
}

QVector<QVector<float>> filters::makeTables(int K, QVector<float> histN) {

	QVector<float> S0(K - 1);
	QVector<float> S1(K - 1);

	float s0 = 0, s1 = 0;

	for (int i = 0; i < K; i++) {
		if (histN[i] > 0)
			s0 = s0 + histN[i] * log(histN[i]);
		S0[i] = s0;
	}
	
	for (int i = K - 1; i >= 0; i--) {
		S1[i] = s1;
		if (histN[i] > 0)
			s1 = s1 + histN[i] * log(histN[i]);
	}
	return {S0, S1};
}

// data when using thresholding
QVector<unsigned char> filters::createNewData(QVector<unsigned char> data, int threshold) {
	QVector<unsigned char> tmp;
	tmp = data;
	for (int j = 0; j < width; j++) //vytvorenie dat
		for (int i = 0; i < height; i++)
			if ((int)origData[j * width + i] < threshold)
				tmp[j * width + i] = (unsigned char)0;
			else
				tmp[j * width + i] = (unsigned char)207;
	return tmp;
}

QVector<double> filters::boundary(QVector<double> data, int threshold) {
	QVector<unsigned char> tmp;
	QVector<double> tmp1;
	tmp = createNewData(dataToChar(data), threshold);
	tmp1.resize(width*height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			tmp1[j * width + i] = 0;
			if((int)tmp[j * width + i] !=0 && ((int)tmp[j * width + (i+1)] == 0 || (int)tmp[j * width + (i - 1)] == 0 ||
				(int)tmp[(j+1) * width + i] == 0 || (int)tmp[(j - 1) * width + i] == 0))
				tmp1[j * width + i] = 207;
		}
	}	
	return tmp1;
}

QVector<double> filters::changeRangeOfData(QVector<int> data) {
	QVector<double> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			tmp[j * width + i] = data.at(j * width + i)/255.;
		}
	}
	return tmp;
}

QVector<double> filters::changeRangeOfData(QVector<double> data, int p) {
	int widthR, heightR;
	widthR = width + 2 * p;
	heightR = height + 2 * p;
	QVector<double> tmp;
	tmp.resize(widthR * heightR);

	for (int j = 0; j < widthR; j++) {
		for (int i = 0; i < heightR; i++) {
			tmp[j * widthR + i] = data.at(j * widthR + i) * 255.;
		}
	}
	return tmp;
}

QVector<double> filters::reflection(QVector<double> data, int p) { //v tejto funkcii ratam s tym ze p = 1 (uz nie uz funguje vseobecne)
	int widthR, heightR;
	widthR = width + 2 * p;
	heightR = height + 2 * p;
	QVector<double> reflected;
	reflected.resize(widthR * heightR);
	reflected.fill(0);

	for (int i = p; i < heightR - p; i++) {
		for (int j = p; j < widthR - p; j++) 
			reflected[j + widthR * i] = data.at((j - p) + width * (i - p));
	}
	
	for (int i = p; i < heightR - p; i++)
		for (int k = 0; k < p; k++) {
			reflected[(p - k - 1) + widthR * i] = reflected.at((p + k) + widthR * i);
			reflected[(height + p + k) + widthR * i] = reflected.at((height + p - k - 1) + widthR * i);
		}

	for (int j = 0; j < widthR; j++)
		for (int k = 0; k < p; k++)	{
			reflected[j + widthR * (p - k - 1)] = reflected.at(j + widthR * (p + k));
			reflected[j + widthR * (width + p + k)] = reflected.at(j + widthR * (width + p - k - 1));
		}

	/*for (int i = 0; i < heightR; i++) {
		for (int j = 0; j < widthR; j++) {
		
			if (i == 0 || i == heightR - 1 ) {				//hore a dole
				if (i == 0)
					reflected[j + widthR * i] = data.at(j);
				else
					reflected[j + widthR * i] = data.at(j + width * (height - 1)); 
			}
			else {
				if (j == 0 || j == widthR - 1) {			//vpravo a vlavoo
					if (j == 0)
						reflected[j + widthR * i] = data.at(width * (i - 1));
					else
						reflected[j + widthR * i] = data.at((width - 1) + width * (i - 1));
				}
				else {
					reflected[j + widthR * i] = data.at(width * (i-1) + (j-1));// data.at(j + widthR * i);
				}
			}
		}
	}*/
	return reflected;
}

QVector<double> filters::updateReflection(QVector<double> data, int p) {
	int widthR, heightR;
	widthR = width + 2 * p;
	heightR = height + 2 * p;
	QVector<double> reflected;
	reflected.resize(widthR * heightR);
	reflected.fill(0);

	for (int i = p; i < heightR - p; i++) {
		for (int j = p; j < widthR - p; j++)
			reflected[j + widthR * i] = data.at(j + widthR * i);
	}

	for (int i = p; i < heightR - p; i++)
		for (int k = 0; k < p; k++) {
			reflected[(p - k - 1) + widthR * i] = data.at((p + k) + widthR * i);
			reflected[(height + p + k) + widthR * i] = data.at((height + p - k - 1) + widthR * i);
		}

	for (int j = 0; j < widthR; j++)
		for (int k = 0; k < p; k++) {
			reflected[j + widthR * (p - k - 1)] = data.at(j + widthR * (p + k));
			reflected[j + widthR * (width + p + k)] = data.at(j + widthR * (width + p - k - 1));
		}

	/*for (int i = 0; i < heightR; i++) {
		for (int j = 0; j < widthR; j++) {

			if (i == 0 || i == heightR - 1) {				//hore a dole
				if (i == 0)
					reflected[j + widthR * i] = data.at(j + widthR * (i + 1));
				else
					reflected[j + widthR * i] = data.at(j + widthR * (i - 1));
			}
			else {
				if (j == 0 || j == widthR - 1) {			//vpravo a vlavoo
					if (j == 0)
						reflected[j + widthR * i] = data.at((j + 1) + widthR * (i));
					else
						reflected[j + widthR * i] = data.at((j - 1) + widthR * (i));
				}
				else {
					reflected[j + widthR * i] = data.at(widthR * (i) + (j));// data.at(j + widthR * i);
				}
			}
		}
	}*/
	return reflected;
}

QVector<double> filters::antireflection(QVector<double> data, int p) { //v tejto funkcii ratam s tym ze p = 1
	int widthR, heightR;
	widthR = width + 2 * p;
	heightR = height + 2 * p;
	QVector<double> antiref;
	antiref.resize(width*height);

	/* for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			antiref[j + width * (i)] = data.at((j + 1) + widthR * (i + 1));
		}
	} */

	for (int j = 0; j < width; j++)
		for (int i = 0; i < height; i++) 
			antiref[j + width * i] = data.at((j + p) + widthR * (i + p));

	return antiref;
}

double filters::M(QVector<double> u, int i, int j, int p, int q) {
	double tmp = u.at((j + q) * (width +2) + (i + p)) - u.at(j * (width + 2) + i);
	if (tmp < 0)
		return tmp * tmp;
	else
		return 0;
}
	
double filters::findmax(double m1, double m2) {
	if (m1 > m2)
		return m1;
	else
		return m2;
}

QVector<double> filters::distFunct(QVector<double> edge) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height +2 * p;
	QVector<double> vysl;
	vysl.resize(width * height);
	QVector<double> un, up;
	QVector<double> ue;
	un.resize(widthR * heightR);
	up.resize(widthR * heightR);
	vysl.fill(0);
	up.fill(0);
	un.fill(0);
	ue = reflection(edge, p);
	//ue = edge;
	int tol = 1;
	double mass = pow(10,6);
	int l = 0;
	int maxIter = 1000;
	double tau = 0.4;
	double h = 1.0;
	int col = 207;
	while (mass > tol && l < maxIter) {
		mass = 0;
		for (int j = 1; j < widthR - 1; j++) {
			for (int i = 1; i < heightR - 1; i++) {
				if (ue[j * widthR + i] != col) {
					un[j * widthR + i] =
						(double)(up[j * widthR + i] + tau - tau / h *
						sqrt(findmax(M(up, i, j, -1, 0), M(up, i, j, 1, 0)) +
							findmax(M(up, i, j, 0, -1), M(up, i, j, 0, 1))));
				}
			}
		}
		for (int j = 0; j < widthR; j++)
			for (int i = 0; i < heightR; i++)
				mass += (un[j * widthR + i] - up[j * widthR + i]) * (un[j * widthR + i] - up[j * widthR + i]);
		mass = sqrt(mass);
		std::cout << "l: " << l << " rezidua: " << mass << std::endl;

		un = updateReflection(un, p);
		up.resize(un.size());
		up = un;
		l++;
	}
	std::cout << "Distanced function bola ziskana po " << l << " iteraciach." << std::endl;
	
	vysl = antireflection(un, p);
	return vysl;
}

QVector<double> filters::distFunctSign(QVector<double> data) {
	QVector<double> matrix;
	QVector<double> dist; 
	dist = distFunct(data);
	matrix.resize(width*height);
	int col = 255;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (data.at(j * width + i) == col)
				matrix[j * width + i] = dist[j * width + i];
			else
				matrix[j * width + i] = (-1*(double)dist[j * width + i]);
		}
	}
	return matrix;
}

QVector<double> filters::aw(QVector<double> data, bool eps) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	QVector<double> pole;
	pole.resize(widthR*heightR);
	pole.fill(0);
	double ux, uy;
	double h = 1.;
	double k = 255 * 255;
	double epsilon = 0.001;

	for (int i = 1; i < widthR - 1; i++) {
		for (int j = 1; j < heightR - 1; j++) {
			ux = (data.at(j * widthR + (i - 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j - 1) * widthR + i) + data.at((j - 1) * widthR + (i - 1))
				- data.at((j + 1) * widthR + i) - data.at((j + 1) * widthR + (i - 1))) / (4 * h);

			double s = sqrt(ux*ux + uy * uy);
			if (eps = true) {
				pole[j * widthR + i] = (1. / (1 + k * s * s));
			}
			else 
				pole[j * widthR + i] = (sqrt(ux *ux + uy * uy + epsilon * epsilon));
		}
	}
	return pole;
}

QVector<double> filters::ae(QVector<double> data, bool eps) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	QVector<double> pole;
	pole.resize(widthR*heightR);
	pole.fill(0);
	double ux, uy;
	double h = 1.;
	double k = 255 * 255;
	double epsilon = 0.001;

	for (int i = 1; i < widthR - 1; i++) {
		for (int j = 1; j < heightR - 1; j++) {
			ux = (data.at(j * widthR + (i + 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j + 1) * widthR + (i + 1)) + data.at((j + 1) * widthR + i)
				- data.at((j - 1) * widthR + (i + 1)) - data.at((j - 1) * widthR + i)) / (4 * h);

			double s = sqrt(ux*ux + uy * uy);
			if (eps = true) {
				pole[j * widthR + i] = (1. / (1 + k * s * s));
			}
			else
				pole[j * widthR + i] = (sqrt(ux *ux + uy * uy + epsilon * epsilon));
		}
	}
	return pole;
}

QVector<double> filters::as(QVector<double> data, bool eps) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	QVector<double> pole;
	pole.resize(widthR*heightR);
	pole.fill(0);
	double ux, uy;
	double h = 1.;
	double k = 255 * 255;
	double epsilon = 0.001;

	for (int i = 1; i < widthR - 1; i++) {
		for (int j = 1; j < heightR - 1; j++) {
			uy = (data.at((j - 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at(j * widthR + (i + 1)) + data.at((j - 1) * widthR + (i + 1))
				- data.at((j - 1) * widthR + (i - 1)) - data.at(j * widthR + (i - 1))) / (4 * h);

			double s = sqrt(ux*ux + uy * uy);
			if (eps = true) {
				pole[j * widthR + i] = (1. / (1 + k * s * s));
			}
			else
				pole[j * widthR + i] = (sqrt(ux *ux + uy * uy + epsilon * epsilon));
		}
	}
	return pole;
}

QVector<double> filters::an(QVector<double> data, bool eps) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	QVector<double> pole;
	pole.resize(widthR*heightR);
	pole.fill(0);
	double ux, uy;
	double h = 1.;
	double k = 255 * 255;
	double epsilon = 0.001;

	for (int i = 1; i < widthR - 1; i++) {
		for (int j = 1; j < heightR - 1; j++) {
			uy = (data.at((j + 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at((j + 1) * widthR + (i - 1)) + data.at(j * widthR + (i - 1))
				- data.at((j + 1) * widthR + (i + 1)) - data.at((j + 1) * widthR + i)) / (4 * h);

			double s = sqrt(ux*ux + uy * uy);
			if (eps = true) {
				pole[j * widthR + i] = (1. / (1 + k * s * s));
			}
			else
				pole[j * widthR + i] = (sqrt(ux *ux + uy * uy + epsilon * epsilon));
		}
	}
	return pole;
}

QVector<double> filters::heatImpl(QVector<double> data, int p) {
	int widthR = width + 2 * p ;
	int heightR = height + 2 * p;
	QVector<double> un, up;
	un.resize(width*height);
	un.fill(0);
	un = reflection(data);
	up = un;
	double tol = pow(10, -6);
	int itermax = 1000;
	double tau = 1.0;
	double h = 1.0;
	double a = tau / (h * h);
	double rez = pow(10, 6);
	double w = 1.15;
	// prerobit na do ~ while
	// do {
	for(int iter = 1; iter <= itermax; iter++) {
		// (*Print["HE: krok=", 1., ", iter=", iter, " rez=", rez]; *)
		std::cout << " HE: krok: " << 1. << " iter: " << iter << " rez: " << rez << std::endl;

		for (int j = p; j < heightR - p; j++) {
			for (int i = p; i < widthR - p; i++) {
				double tmp = (1. / (1. + 4 * a))*(up.at(j * widthR + i) +
					a * (un.at(j * widthR + (i + 1)) +
						un.at(j * widthR + (i - 1)) +
						un.at((j + 1) * widthR + i) +
						un.at((j - 1) * widthR + i)));
				un[j * widthR + i] =
					un.at(j * widthR + i) +
					w * (tmp - un.at(j * widthR + i));
			}
		}
		rez = 0;
		for (int j = p; j < heightR - p; j++) {
			for (int i = p; i < widthR - p; i++) {
				double tmp = (1. + 4 * a) * un.at(j * widthR + i) -
					a * (un.at(j * widthR + (i + 1)) +
						un.at(j * widthR + (i - 1)) + 
						un.at((j - 1) * widthR + i) +
						un.at((j + 1) * widthR + i)) -
					up.at(j * widthR + i);
				rez += tmp * tmp;
			}
		}
		if (rez < tol)
			break;
	} // while ();
	un = antireflection(un, p);
	up = un;

	return up;
}

QVector<double> filters::subSurf(QVector<double> data, QVector<double> tData) {
	int p = 1;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	QVector<double> uk1, up, un, uhe, up1;
	QVector<double> qepm, qwpm, qspm, qnpm, qe, qw, qs, qn;
	QVector<double> uf;
	uf.resize(width*height);
	uk1.resize(width*height);
	uk1 = up = un;
	up = reflection(data, p);
	uhe.resize(widthR*heightR);
	uhe = up1;
	un = up;
	//pic[0] = data;
	double tol = 0.5;
	int itermax = 100;
	double tau = 1.0;
	double h = 1.0;
	double a = tau / (h*h);
	double k = 255*255;
	double sigma = 0.25;
	double epsilon = 0.001;
	double w = 1.15;

	uk1 = heatImpl(tData);
	uk1 = reflection(uk1);

	qepm = ae(uk1, true);
	qwpm = aw(uk1, true);
	qspm = as(uk1, true);
	qnpm = an(uk1, true);

	qe = ae(un, false);
	qw = aw(un, false);
	qs = as(un, false);
	qn = an(un, false);

	for (int t = 0; t < 200; t++) {
		double rez = pow(10,6);

		for (int iter = 0; iter < itermax; iter++) {
			// (*Print["krok=", t, ", iter=", iter, " rez=", rez]; *)
			// std::cout << "krok: " << t << " iter: " << iter << " rez: " << rez << std::endl;

			for (int i = 1; i < widthR - 1; i++) {
				for (int j = 1; j < heightR - 1; j++) {
					double avg = (1. / 4.)*(qe.at(j * widthR + i)
						+ qw.at(j * widthR + i)
						+ qs.at(j * widthR + i)
						+ qn.at(j * widthR + i));

					double	tmps = (1. / qe.at(j * widthR + i)) * qepm.at(j * widthR + i) +
						(1. / qw.at(j * widthR + i)) * qwpm.at(j * widthR + i) +
						(1. / qs.at(j * widthR + i)) * qspm.at(j * widthR + i) +
						(1. / qn.at(j * widthR + i)) * qnpm.at(j * widthR + i);

					double tmp = (up.at(j * widthR + i) -
						(-a * avg)*(qepm.at(j * widthR + i) * un.at(j * widthR + (i + 1)) * (1. / qe.at(j * widthR + i)) +
							un.at(j * widthR + (i - 1)) * qwpm.at(j * widthR + i) * (1. / qw.at(j * widthR + i)) +
							un.at((j + 1) * widthR + i) * qnpm.at(j * widthR + i) * (1. / qn.at(j * widthR + i)) +
							un.at((j - 1) * widthR + i) * qspm.at(j * widthR + i) * (1. / qs.at(j * widthR + i)))) / (1 + a * tmps*avg);

					un[j * widthR + i] = un.at(j * widthR + i) + w * (tmp - un.at(j * widthR + i));
				}
			}
			rez = 0.;
			for (int i = 1; i < widthR - 1; i++) {
				for (int j = 1; j < heightR - 1; j++) {
					double avg = (1. / 4.)*(qe.at(j * widthR + i) 
						+ qw.at(j * widthR + i)
						+ qs.at(j * widthR + i) 
						+ qn.at(j * widthR + i));
					double tmps = (1. / qe.at(j * widthR + i)) * qepm.at(j * widthR + i)
						+ (1. / qw.at(j * widthR + i)) * qwpm.at(j * widthR + i)
						+ (1. / qs.at(j * widthR + i)) * qspm.at(j * widthR + i)
						+ (1. / qn.at(j * widthR + i)) * qnpm.at(j * widthR + i);
					double tmp = (up.at(j * widthR + i) - ((1 + a * tmps*avg)* un.at(j * widthR + i) + 
						(-a * avg)*(qepm.at(j * widthR + i) * un.at(j * widthR + (i + 1)) * (1. / qe.at(j * widthR + i))
							+ un.at(j * widthR + (i - 1)) * qwpm.at(j * widthR + i) * (1. / qw.at(j * widthR + i)) +
							un.at((j + 1) * widthR + i) * qnpm.at(j * widthR + i) * (1. / qn.at(j * widthR + i)) +
							un.at((j - 1) * widthR + i) * qspm.at(j * widthR + i) * (1. / qs.at(j * widthR + i)))));
					rez += tmp * tmp;
				}
			}
			if (rez < tol) {
				std::cout << "krok: " << t << " iter: " << iter << " rez: " << rez << std::endl;
				break;
			}
		}
		up = un;
		//pic[t] = uf;
	}	
	uf = antireflection(un, p);
	return uf;
}

QVector<double> filters::niblackThreshold(QVector<double> data, int p) {
	QVector<double> tmp, tmp1, tmp2, thresholds;
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;
	double TT = 20, r = p*p;
	tmp1 = heatImpl(data, p); //u
	tmp2 = heatImpl(pow2(data), p); //uu

	tmp1 = reflection(data, p); 
	tmp2 = reflection(pow2(data), p); 

	for (int i = p; i < height + p; i++)
		for (int j = p; j < width + p; j++) {
			tmp2[j * widthR + i] = sqrt(tmp2[j * widthR + i] - pow(tmp1[j * widthR + i], 2));
			if (tmp2[j * widthR + i] < TT / 255. && tmp1[j * widthR + i] < 70 / 255.)
				tmp2[j * widthR + i] = tmp2[j * widthR + i] + 30 / 255.;
			if (tmp2[j * widthR + i] < TT / 255. && tmp1[j * widthR + i] >= 70 / 255.)
				tmp2[j * widthR + i] = tmp2[j * widthR + i] - 30 / 255.;
		}

	thresholds.resize(tmp1.size());
	for (int i = p; i < height + p; i++)
		for (int j = p; j < width + p; j++) 
			thresholds[j * widthR + i] = tmp1[j * widthR + i] + 0.18*tmp2[j * widthR + i];  //thresholds

	tmp = reflection(data, p);

	for (int i = p; i < height + p; i++)
		for (int j = p; j < width + p; j++)
			if (tmp[j * widthR + i] <= thresholds[j * widthR + i])
				tmp[j * widthR + i] = 0;
			else
				tmp[j * widthR + i] = 1;

	double cminv = 50/255.;
	for (int i = p; i < height + p; i++) {
		for (int j = p; j < width + p; j++) {
			double min = 10, max = -1;
			for (int ii = i - p; ii <= i + p; ii++)
				for (int jj = j - p; jj <= j + p; jj++) 
					//if(pow(i-ii,2)+pow(j-jj,2)<=p*p) 
					{
						if (tmp[jj * widthR + ii] < min)
							min = tmp.at(jj * widthR + ii);
						if (tmp[jj * widthR + ii] > max)
							max = tmp.at(jj * widthR + ii);
					}
			double pom = 0.5*(min + max);
			if (pom < cminv)
				thresholds[j * widthR + i] = 1;
		}
	}

	//final thresholding
	for (int i = p; i < height + p; i++) 
		for (int j = p; j < width + p; j++) 
			if (tmp[j * widthR + i] <= thresholds[j * widthR + i])
				tmp1[j * widthR + i] = 0;
			else
				tmp1[j * widthR + i] = 1;

	 tmp1 = antireflection(tmp1, p);
	 tmp1 = changeRangeOfData(tmp1);

	return tmp1;
}

QVector<double> filters::pow2(QVector<double> data) {
	QVector<double> tmp;
	tmp.resize(data.size());
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tmp[j * width + i] = data.at(j * width + i)* data.at(j * width + i);

	return tmp;
}
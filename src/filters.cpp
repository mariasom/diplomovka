#include "filters.h"

filters::filters() {
}

filters::~filters() {
	origData.clear();
}

filters::filters(int widthOrig, int heightOrig, QVector<unsigned char> oData, int pp) {
	width = widthOrig;
	height = heightOrig;

	origData = dataToDouble(oData);
	histogram(origData);
	p = pp;
	widthR = width + 2 * p;
	heightR = height + 2 * p;
}

QVector<double> filters::dataToDouble(QVector<unsigned char> oData) {
	QVector<double> tmp;
	tmp.reserve(oData.size());
	std::copy(oData.cbegin(), oData.cend(), std::back_inserter(tmp));
	return tmp;
}

QVector<int> filters::dataToInt(QVector<unsigned char> oData) {
	QVector<int> tmp;
	tmp.reserve(oData.size());
	std::copy(oData.cbegin(), oData.cend(), std::back_inserter(tmp));
	return tmp;
}

QVector<int> filters::dataToInt(QVector<double> oData) {
	QVector<int> tmp;
	tmp.reserve(oData.size());
	std::copy(oData.cbegin(), oData.cend(), std::back_inserter(tmp));
	return tmp;
}

QVector<unsigned char> filters::dataToChar(QVector<double> data) {
	QVector<unsigned char> tmp;
	tmp.reserve(data.size());
	std::copy(data.cbegin(), data.cend(), std::back_inserter(tmp));
	return tmp;
}

QVector<double> filters::changeRangeOfData(QVector<int> data) {
	QVector<double> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			tmp[j * width + i] = data.at(j * width + i) / 255.;
		}
	}
	return tmp;
}

QVector<double> filters::changeRangeOfData(QVector<double> data) {
	QVector<double> tmp;
	tmp.resize(width * height);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			tmp[j * width + i] = data.at(j * width + i) * 255.;
		}
	}
	return tmp;
}

void filters::histogram(QVector<double> data) {
	hist.resize(256);
	hist.fill(0);
	for (int i = 0; i < width*height; i++) 
		hist[int(data[i])]++;
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
		wB += hist[t];               
		if (wB == 0) 
			continue;

		wF = total - wB;             
		if (wF == 0) 
			break;

		sumB += (float)(t * hist[t]);

		float mB = sumB / wB;            
		float mF = (sum - sumB) / wF;    

		float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);		

		if (varBetween > varMax) {	
			varMax = varBetween;
			threshold = t;
		}
	}
	std::cout << "treshold: " << threshold << std::endl;
	return threshold;
}

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
	int Hmax = -100000;
	threshold = -1;

	for (int q = 0; q < K - 2; q++) {
		p0 = p0 + histN[q];
		p1 = 1 - p0;
		float h0 = 0, h1 = 0, h = 0;
		if (p0 > 0) 
			h0 = -(1. / p0)*S[0][q] + log(p0);
		else
			h0 = 0;

		if (p1 > 0) 
			h1 = -(1. / p1)*S[1][q] + log(p1);
		else
			h1 = 0;
		h = h0 + h1; 

		if (h > Hmax) {
			Hmax = h;
			threshold = q;
		}
	}
	std::cout << "treshold: " << threshold << std::endl;
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

// creating data when using thresholding
QVector<unsigned char> filters::createNewData(QVector<unsigned char> data, int threshold) {
	QVector<unsigned char> tmp;
	tmp = data;
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			if ((int)origData[j * width + i] < threshold)
				tmp[j * width + i] = (unsigned char)0;
			else
				tmp[j * width + i] = (unsigned char)255;
	return tmp;
}

QVector<double> filters::boundary(QVector<double> data, int threshold) {
	QVector<unsigned char> tmp;
	QVector<double> tmp1;
	if (threshold != -1) 
		tmp = createNewData(dataToChar(data), threshold);
	else
		tmp = dataToChar(data);
	tmp1.resize(width*height);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			tmp1[j * width + i] = 0;
			if((int)tmp[j * width + i] !=0 && ((int)tmp[j * width + (i+1)] == 0 || (int)tmp[j * width + (i - 1)] == 0 ||
				(int)tmp[(j+1) * width + i] == 0 || (int)tmp[(j - 1) * width + i] == 0))
				tmp1[j * width + i] = 255;
		}
	}	
	return tmp1;
}

QVector<double> filters::reflection(QVector<double> data) {	
	QVector<double> reflected;
	reflected.resize(widthR * heightR);
	reflected.fill(0);

	for (int j = p; j < heightR - p; j++) {
		for (int i = p; i < widthR - p; i++)
			reflected[j * widthR + i] = data.at((j - p) * width + (i - p));
	}

	for (int j = p; j < heightR - p; j++)
		for (int k = 0; k < p; k++) {
			reflected[(p - k - 1) + widthR * j] = reflected.at((p + k) + widthR * j);
			reflected[(width + p + k) + widthR * j] = reflected.at((width + p - k - 1) + widthR * j);
		}

	for (int i = 0; i < widthR; i++)
		for (int k = 0; k < p; k++) {
			reflected[i + widthR * (p - k - 1)] = reflected.at(i + widthR * (p + k));
			reflected[i + widthR * (height + p + k)] = reflected.at(i + widthR * (height + p - k - 1));
		}

	return reflected;
}

QVector<double> filters::updateReflection(QVector<double> data) {
	QVector<double> reflected;
	reflected.resize(widthR * heightR);
	reflected.fill(0);

	for (int j = p; j < heightR - p; j++) {
		for (int i = p; i < widthR - p; i++)
			reflected[i + widthR * j] = data.at(i + widthR * j);
	}

	for (int j = p; j < heightR - p; j++)
		for (int k = 0; k < p; k++) {
			reflected[(p - k - 1) + widthR * j] = data.at((p + k) + widthR * j);
			reflected[(width + p + k) + widthR * j] = data.at((width + p - k - 1) + widthR * j);
		}

	for (int i = 0; i < widthR; i++)
		for (int k = 0; k < p; k++) {
			reflected[i + widthR * (p - k - 1)] = data.at(i + widthR * (p + k));
			reflected[i + widthR * (height + p + k)] = data.at(i + widthR * (height + p - k - 1));
		}
	return reflected;
}

QVector<double> filters::antireflection(QVector<double> data) {
	QVector<double> antiref;
	antiref.resize(width*height);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) 
			antiref[j * width + i] = data.at((j + p) * widthR + (i + p));

	return antiref;
}

double filters::M(QVector<double> u, int i, int j, int p, int q) {
	double tmp = u.at((j + q) * (widthR) + (i + p)) - u.at(j * (widthR) + i);
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
	QVector<double> vysl;
	vysl.resize(width * height);
	QVector<double> un, up;
	QVector<double> ue;
	un.resize(widthR * heightR);
	un.fill(0);
	up = un;
	vysl.fill(0);
	ue = reflection(edge);
	int tol = 1;
	double mass = pow(10,6);
	int l = 0;
	int maxIter = 1000;
	double tau = 0.4;
	double h = 1.0;
	int col = 255;
	while (mass > tol && l < maxIter) {
		mass = 0;
		for (int j = 1; j < heightR - 1; j++) {
			for (int i = 1; i < widthR - 1; i++) {
				if (ue[j * widthR + i] != col) {
					un[j * widthR + i] =
						(double)(up[j * widthR + i] + tau - tau / h *
						sqrt(findmax(M(up, i, j, -1, 0), M(up, i, j, 1, 0)) +
							findmax(M(up, i, j, 0, -1), M(up, i, j, 0, 1))));
				}
			}
		}
		for (int j = 0; j < heightR; j++)
			for (int i = 0; i < widthR; i++)
				mass += (un[j * widthR + i] - up[j * widthR + i]) * (un[j * widthR + i] - up[j * widthR + i]);
		mass = sqrt(mass);
		std::cout << "l: " << l << " rezidua: " << mass << std::endl;

		un = updateReflection(un);
		up.resize(un.size());
		up = un;
		l++;
	}
	std::cout << "Distanced function bola ziskana po " << l << " iteraciach." << std::endl;
	
	vysl = antireflection(un);
	return vysl;
}

QVector<double> filters::distFunctSign(QVector<double> data) {
	QVector<double> matrix, dist; 
	dist = distFunct(boundary(data));
	matrix.resize(width*height);
	int col = 255;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (data.at(j * width + i) == col)
				matrix[j * width + i] = (1.0 * dist[j * width + i]);
			else
				matrix[j * width + i] = (-1.*(double)dist[j * width + i]);
		}
	}
	return matrix;
}

void filters::grad(QVector<double> data, double h, double k, double epsilon) {
	qe.resize(widthR*heightR);
	qw.resize(widthR*heightR);
	qs.resize(widthR*heightR);
	qn.resize(widthR*heightR);
	double ux, uy;
	double s;
	for (int j = 1; j < heightR - 1; j++) {
		for (int i = 1; i < widthR - 1; i++) {
			// an
			uy = (data.at((j + 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at((j + 1) * widthR + (i - 1)) + data.at(j * widthR + (i - 1))
				- data.at((j + 1) * widthR + (i + 1)) - data.at(j * widthR + (i + 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qn[j * widthR + i] = (sqrt(s + epsilon * epsilon));

			// aw
			ux = (data.at(j * widthR + (i - 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j - 1) * widthR + i) + data.at((j - 1) * widthR + (i - 1))
				- data.at((j + 1) * widthR + i) - data.at((j + 1) * widthR + (i - 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qw[j * widthR + i] = (sqrt(s + epsilon * epsilon));

			// ae
			ux = (data.at(j * widthR + (i + 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j + 1) * widthR + (i + 1)) + data.at((j + 1) * widthR + i)
				- data.at((j - 1) * widthR + (i + 1)) - data.at((j - 1) * widthR + i)) / (4 * h);

			s = ux * ux + uy * uy;
			qe[j * widthR + i] = (sqrt(s + epsilon * epsilon));

			// as
			uy = (data.at((j - 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at(j * widthR + (i + 1)) + data.at((j - 1) * widthR + (i + 1))
				- data.at((j - 1) * widthR + (i - 1)) - data.at(j * widthR + (i - 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qs[j * widthR + i] = (sqrt(s + epsilon * epsilon));
		}
	}
}

void filters::grad2(QVector<double> data, double h, double k, double epsilon) {
	qepm.resize(widthR*heightR);
	qwpm.resize(widthR*heightR);
	qspm.resize(widthR*heightR);
	qnpm.resize(widthR*heightR);
	double s;
	double ux, uy;
	for (int i = 1; i < heightR - 1; i++) {
		for (int j = 1; j < widthR - 1; j++) {

			// an
			uy = (data.at((j + 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at((j + 1) * widthR + (i - 1)) + data.at(j * widthR + (i - 1))
				- data.at((j + 1) * widthR + (i + 1)) - data.at(j * widthR + (i + 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qnpm[j * widthR + i] = (1. / (1 + k * s));

			// aw
			ux = (data.at(j * widthR + (i - 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j - 1) * widthR + i) + data.at((j - 1) * widthR + (i - 1))
				- data.at((j + 1) * widthR + i) - data.at((j + 1) * widthR + (i - 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qwpm[j * widthR + i] = (1. / (1 + k * s));

			// ae
			ux = (data.at(j * widthR + (i + 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j + 1) * widthR + (i + 1)) + data.at((j + 1) * widthR + i)
				- data.at((j - 1) * widthR + (i + 1)) - data.at((j - 1) * widthR + i)) / (4 * h);

			s = ux * ux + uy * uy;
			qepm[j * widthR + i] = (1. / (1 + k * s));

			// as
			uy = (data.at((j - 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at(j * widthR + (i + 1)) + data.at((j - 1) * widthR + (i + 1))
				- data.at((j - 1) * widthR + (i - 1)) - data.at(j * widthR + (i - 1))) / (4 * h);

			s = ux * ux + uy * uy;
			qspm[j * widthR + i] = (1. / (1 + k * s));
		}
	}
}

void filters::grad3(QVector<double> data, double h, double k, double epsilon, double sigma) {
	qepm.resize(widthR*heightR);
	qwpm.resize(widthR*heightR);
	qspm.resize(widthR*heightR);
	qnpm.resize(widthR*heightR);
	QVector<double> oData;
	oData = heatImpl(origData, sigma);
	double s1,s2;
	double ux, uy, uxx, uyy;
	for (int j = 1; j < heightR - 1; j++) {
		for (int i = 1; i < widthR - 1; i++) {
			// da sa zoptimalizovat 
			// an
			uy = (data.at((j + 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at((j + 1) * widthR + (i - 1)) + data.at(j * widthR + (i - 1))
				- data.at((j + 1) * widthR + (i + 1)) - data.at(j * widthR + (i + 1))) / (4 * h);

			uyy = (oData.at((j + 1) * widthR + i) - oData.at(j * widthR + i)) / h;
			uxx = (oData.at((j + 1) * widthR + (i - 1)) + oData.at(j * widthR + (i - 1))
				- oData.at((j + 1) * widthR + (i + 1)) - oData.at(j * widthR + (i + 1))) / (4 * h);

			s2 = uxx * uxx + uyy * uyy;
			s1 = ux * ux + uy * uy;
			qnpm[j * widthR + i] = ((0.8 / (1 + k * s1)) + (0.2 / (1 + k * s2)));

			// aw
			ux = (data.at(j * widthR + (i - 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j - 1) * widthR + i) + data.at((j - 1) * widthR + (i - 1))
				- data.at((j + 1) * widthR + i) - data.at((j + 1) * widthR + (i - 1))) / (4 * h);

			uxx = (oData.at(j * widthR + (i - 1)) - oData.at(j * widthR + i)) / h;
			uyy = (oData.at((j - 1) * widthR + i) + oData.at((j - 1) * widthR + (i - 1))
				- oData.at((j + 1) * widthR + i) - oData.at((j + 1) * widthR + (i - 1))) / (4 * h);

			s2 = uxx * uxx + uyy * uyy;
			s1 = ux * ux + uy * uy;
			qwpm[j * widthR + i] = ((0.8 / (1 + k * s1)) + (0.2 / (1 + k * s2)));

			// ae
			ux = (data.at(j * widthR + (i + 1)) - data.at(j * widthR + i)) / h;
			uy = (data.at((j + 1) * widthR + (i + 1)) + data.at((j + 1) * widthR + i)
				- data.at((j - 1) * widthR + (i + 1)) - data.at((j - 1) * widthR + i)) / (4 * h);

			uxx = (oData.at(j * widthR + (i + 1)) - oData.at(j * widthR + i)) / h;
			uyy = (oData.at((j + 1) * widthR + (i + 1)) + oData.at((j + 1) * widthR + i)
				- oData.at((j - 1) * widthR + (i + 1)) - oData.at((j - 1) * widthR + i)) / (4 * h);

			s2 = uxx * uxx + uyy * uyy;
			s1 = ux * ux + uy * uy;
			qepm[j * widthR + i] = ((0.8 / (1 + k * s1)) + (0.2 / (1 + k * s2)));

			// as
			uy = (data.at((j - 1) * widthR + i) - data.at(j * widthR + i)) / h;
			ux = (data.at(j * widthR + (i + 1)) + data.at((j - 1) * widthR + (i + 1))
				- data.at((j - 1) * widthR + (i - 1)) - data.at(j * widthR + (i - 1))) / (4 * h);

			uyy = (oData.at((j - 1) * widthR + i) - oData.at(j * widthR + i)) / h;
			uxx = (oData.at(j * widthR + (i + 1)) + oData.at((j - 1) * widthR + (i + 1))
				- oData.at((j - 1) * widthR + (i - 1)) - oData.at(j * widthR + (i - 1))) / (4 * h);

			s2 = uxx * uxx + uyy * uyy;
			s1 = ux * ux + uy * uy;
			qspm[j * widthR + i] = ((0.8 / (1 + k * s1)) + (0.2 / (1 + k * s2)));
		}
	}
}

QVector<double> filters::heatImpl(QVector<double> data, double timeStep) {
	QVector<double> un, up;
	un.resize(width*height);
	un.fill(0);
	un = reflection(data);
	up = un;
	double tol = pow(10, -6);
	int itermax = 1000;
	double tau = 1.0;
	double h = 1.0;
	// double a = tau / (h * h);
	double rez = pow(10, 6);
	double w = 1.15;

	for(int iter = 1; iter <= itermax; iter++) {
		for (int j = p; j < heightR - p; j++) {
			for (int i = p; i < widthR - p; i++) {
				double tmp = (1. / (1. + 4 * timeStep))*(up.at(j * widthR + i) +
					timeStep * (un.at(j * widthR + (i + 1)) +
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
				double tmp = (1. + 4 * timeStep) * un.at(j * widthR + i) -
					timeStep * (un.at(j * widthR + (i + 1)) +
						un.at(j * widthR + (i - 1)) + 
						un.at((j - 1) * widthR + i) +
						un.at((j + 1) * widthR + i)) -
					up.at(j * widthR + i);
				rez += tmp * tmp;
			}
		}
		if (rez < tol) {
			std::cout << " HE: iter: " << iter << " rez: " << rez << std::endl;
			break;
		}
	} 
	up = un;
	return up;
}

QVector<double> filters::subSurf(QVector<double> data, QVector<double> tData, int steps , double sigma, double tau, double k) {
	QVector<double> uk1, up, un, uhe, up1, avg;
	QVector<double> uf;
	uf.resize(width*height);
	uk1.resize(width*height);
	uk1 = up = un;
	up = reflection(data);
	uhe.resize(widthR*heightR);
	uhe = up1;
	un = up;
	//pic[0] = data;
	double tol = 0.5;
	int itermax = 1000;
	double h = 1.0;
	double epsilon = pow(10,-6);
	double w = 1.15;

	uk1 = heatImpl(tData, sigma);
	grad3(uk1, h, k, epsilon, sigma);

	for (int t = 0; t < steps; t++) {
		double rez = pow(10,6);

		grad(un, h, k, epsilon);
		avg = countAvg();
		/*qe = ae(un, false);
		qw = aw(un, false);
		qs = as(un, false);
		qn = an(un, false);*/

		for (int iter = 0; iter < itermax; iter++) {

			for (int j = 1; j < heightR - 1; j++) {
				for (int i = 1; i < widthR - 1; i++) {

					double	tmps = ( qepm.at(j * widthR + i) / qe.at(j * widthR + i)) +
						(qwpm.at(j * widthR + i)/qw.at(j * widthR + i)) +
						(qspm.at(j * widthR + i) / qs.at(j * widthR + i)) +
						(qnpm.at(j * widthR + i)/ qn.at(j * widthR + i));

					double tmp = (up.at(j * widthR + i) -
						(-tau * avg.at(j * widthR + i))*(qepm.at(j * widthR + i) * un.at(j * widthR + (i + 1)) * (1. / qe.at(j * widthR + i)) +
							un.at(j * widthR + (i - 1)) * qwpm.at(j * widthR + i) * (1. / qw.at(j * widthR + i)) +
							un.at((j + 1) * widthR + i) * qnpm.at(j * widthR + i) * (1. / qn.at(j * widthR + i)) +
							un.at((j - 1) * widthR + i) * qspm.at(j * widthR + i) * (1. / qs.at(j * widthR + i)))) / (1 + tau * tmps*avg.at(j * widthR + i));

					un[j * widthR + i] = un.at(j * widthR + i) + w * (tmp - un.at(j * widthR + i));
				}
			}
			rez = 0.;
			for (int j = 1; j < heightR - 1; j++) {
				for (int i = 1; i < widthR - 1; i++) {
					double tmps = (qepm.at(j * widthR + i) / qe.at(j * widthR + i))
						+ (qwpm.at(j * widthR + i) / qw.at(j * widthR + i))
						+ (qspm.at(j * widthR + i) / qs.at(j * widthR + i)) 
						+ (qnpm.at(j * widthR + i) / qn.at(j * widthR + i));
					double tmp = (up.at(j * widthR + i) - ((1 + tau * tmps*avg.at(j * widthR + i))* un.at(j * widthR + i) +
						(-tau * avg.at(j * widthR + i))*(qepm.at(j * widthR + i) * un.at(j * widthR + (i + 1)) * (1. / qe.at(j * widthR + i))
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
	uf = antireflection(un);
	return uf;
}

QVector<double> filters::countAvg() {
	QVector<double> tmp;
	tmp.resize(widthR*heightR);
	double a = 1. / 4.;
	for (int j = 1; j < heightR - 1; j++) {
		for (int i = 1; i < widthR - 1; i++) {
			tmp[j * widthR + i] = a*(qe.at(j * widthR + i)
				+ qw.at(j * widthR + i)
				+ qs.at(j * widthR + i)
				+ qn.at(j * widthR + i));
		}
	}
	return tmp;
}

QVector<double> filters::niblackThreshold(QVector<double> data, double timeStep) {
	QVector<double> tmp, tmp1, tmp2, thresholds;
	double TT = 20/255.,  r2 = p*p;
	double m = 70 / 255.;
	double d = 20 / 255.;
	tmp1 = heatImpl(data, timeStep); //u
	tmp2 = heatImpl(pow2(data), timeStep); //uu

	for (int  j = p; j < height + p; j++)
		for (int i = p; i < width + p; i++) {
			tmp2[j * widthR + i] = sqrt(tmp2[j * widthR + i] - pow(tmp1[j * widthR + i], 2));
			if (tmp2[j * widthR + i] < TT && tmp1[j * widthR + i] < m)
				tmp2[j * widthR + i] = tmp2[j * widthR + i] + d;
			if (tmp2[j * widthR + i] < TT && tmp1[j * widthR + i] >= m)
				tmp2[j * widthR + i] = tmp2[j * widthR + i] - d;
		}

	thresholds.resize(tmp1.size());
	for (int j = p; j < height + p; j++)
		for (int i = p; i < width + p; i++) 
			thresholds[j * widthR + i] = tmp1[j * widthR + i] + 0.18*tmp2[j * widthR + i];  
	tmp = reflection(data);

	double cminv = 50/255.;
	for (int j = p; j < height + p; j++) {
		for (int i = p; i < width + p; i++) {
			double min = 10, max = -1;
			for (int jj = j - p; jj <= j + p; jj++)
				for (int ii = i - p; ii <= i + p; ii++) 
					if(pow(i-ii,2)+pow(j-jj,2)<= r2 ) {
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

	for (int j = p; j < height + p; j++)		
		for (int i = p; i < width + p; i++) 
			if (tmp[j * widthR + i] <= thresholds[j * widthR + i])
				tmp1[j * widthR + i] = 0;
			else
				tmp1[j * widthR + i] = 255;

	 tmp1 = antireflection(tmp1);
	 // tmp1 = changeRangeOfData(tmp1);
	return tmp1;
}

QVector<double> filters::pow2(QVector<double> data) {
	QVector<double> tmp;
	tmp.resize(data.size());
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			tmp[j * width + i] = data.at(j * width + i)* data.at(j * width + i);
	return tmp;
}

QVector<double> filters::bernsenThreshold(QVector<double> data) {
	QVector<double> tmp, cont, thrshld;

	int cmin = 40;
	int r = p*p;
	tmp = reflection(data);
	cont.resize(tmp.length());
	thrshld.resize(tmp.length());
	int q = 0; //	kedze mame vzdy tmave pozadie
	for (int j = p; j < heightR; j++) {
		for (int i = p; i < widthR; i++) {
			double Imin = 300, Imax = -1, c;
			for (int jj = j - p; jj <= j + p; jj++)
				for (int ii = i - p; ii <= i + p; ii++) {
					if (pow(i - ii, 2) + pow(j - jj, 2) <= r) {
						if (tmp[jj * widthR + ii] < Imin)
							Imin = tmp.at(jj * widthR + ii);
						if (tmp[jj * widthR + ii] > Imax)
							Imax = tmp.at(jj * widthR + ii);
					}
				}
			cont[j * widthR + i] = Imax - Imin;
			if (cont[j * widthR + i] >= cmin)
				thrshld[j * widthR + i] = (Imax + Imin) / 2.;
			else
				thrshld[j * widthR + i] = q;
		}
	}

	for (int j = 0; j < heightR; j++) {
		for (int i = 0; i < widthR; i++) {
			if (cont[j * widthR + i] < cmin) {
				if (thrshld[j * widthR + i] < cmin)
					tmp[j * widthR + i] = 0;
				else
					tmp[j * widthR + i] = 255;
			}
			else {
				if (tmp[j * widthR + i] < thrshld[j * widthR + i])
					tmp[j * widthR + i] = 0;
				else  tmp[j * widthR + i] = 255;
			}
		}
	}
	tmp = antireflection(tmp);
	return tmp;
}

QVector<double> filters::thresholdFunction(QVector<unsigned char> initConData) {
	QVector<double> z;
	z.resize(height*width);
	z.fill(-1);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if ((int)initConData[j * width + i] != 0)
				z[j * width + i] = 1.;
		}
	}

	return z;
}

QVector<unsigned char> filters::dataDifference(QVector<unsigned char> tData) {
	QVector<unsigned char> newData;
	newData.resize(width*height);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			newData[j * width + i] = (unsigned char)((int)((origData.at(j * width + i) + tData.at(j * width + i)) / 2. + 0.5));
		}
	}

	return newData;
}

QVector<double>  filters::cutDataAt(QVector<double> z, double value) {
	QVector<double> tmp;
	tmp.resize(width*height);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			if (value < z.at(width * j + i))
				tmp[width * j + i] = z.at(width * j + i);
			else
				tmp[width * j + i] = value;
		}

	return tmp;
}

QVector<double> filters::hybBernsenAndNiblack(QVector<double> data, double timeStep) {
	QVector<double> tmp, cont, thrshld;
	QVector<double> tmp1, tmp2;
	double r2 = p * p;
	double cmin = 50 / 255.;
	
	tmp1 = heatImpl(data, timeStep); 
	tmp2 = heatImpl(pow2(data), timeStep); 
	tmp = reflection(data);
	cont.resize(tmp.length());
	thrshld.resize(tmp.length());
	int q = 0;
	for (int j = p; j < heightR; j++) {
		for (int i = p; i < widthR; i++) {
			double Imin = 300, Imax = -1, c;
			for (int jj = j - p; jj <= j + p; jj++) {
				for (int ii = i - p; ii <= i + p; ii++)
					if (pow(i - ii, 2) + pow(j - jj, 2) <= r2) {
						if (tmp[jj * widthR + ii] < Imin)
							Imin = tmp.at(jj * widthR + ii);
						if (tmp[jj * widthR + ii] > Imax)
							Imax = tmp.at(jj * widthR + ii);
					}
				}
			cont[j * widthR + i] = Imax - Imin;
			if (cont[j * widthR + i] >= cmin)
				thrshld[j * widthR + i] = tmp1[j * widthR + i] + 0.18*tmp2[j * widthR + i];
			else
				thrshld[j * widthR + i] = q;
		}
	}

	for (int j = 0; j < heightR; j++) {
		for (int i = 0; i < widthR; i++) {
			if (cont[j * widthR + i] < cmin) {
				if (thrshld[j * widthR + i] < cmin)
					tmp[j * widthR + i] = 0;
				else
					tmp[j * widthR + i] = 255;
			}
			else {
				if (tmp[j * widthR + i] < thrshld[j * widthR + i])
					tmp[j * widthR + i] = 0;
				else  tmp[j * widthR + i] = 255;
			}
		}
	}
	tmp = antireflection(tmp);
	return tmp;
}

QVector<double> filters::sauvolaThreshold(QVector<double> data, double timeStep) {
	QVector<double> tmp, tmp1, tmp2, thresholds;
	double TT = 20 / 255., r2 = p * p;
	double m = 70 / 255.;
	double d = 20 / 255.;
	tmp1 = heatImpl(data, timeStep); //u
	tmp2 = heatImpl(pow2(data), timeStep); //uu
	double sigmaMax = 128 / 255.;
	thresholds.resize(tmp1.size());
	for (int j = p; j < height + p; j++)
		for (int i = p; i < width + p; i++)
			thresholds[j * widthR + i] = tmp1[j * widthR + i] * (1 + 0.18*((tmp2[j * widthR + i]/sigmaMax) - 1));
	tmp = reflection(data);

	double cminv = 50 / 255.;
	for (int j = p; j < height + p; j++) {
		for (int i = p; i < width + p; i++) {
			double min = 10, max = -1;
			for (int jj = j - p; jj <= j + p; jj++)
				for (int ii = i - p; ii <= i + p; ii++)
					if (pow(i - ii, 2) + pow(j - jj, 2) <= r2) {
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

	for (int j = p; j < height + p; j++)
		for (int i = p; i < width + p; i++)
			if (tmp[j * widthR + i] <= thresholds[j * widthR + i])
				tmp1[j * widthR + i] = 0;
			else
				tmp1[j * widthR + i] = 255;

	tmp1 = antireflection(tmp1);
	return tmp1;
}

QVector<double> filters::hybBernsenAndSauvola(QVector<double> data, double timeStep) {
	QVector<double> tmp, cont, thrshld;
	QVector<double> tmp1, tmp2;
	double r2 = p * p;
	double cmin = 50 / 255.;

	tmp1 = heatImpl(data, timeStep);
	tmp2 = heatImpl(pow2(data), timeStep);
	tmp = reflection(data);
	cont.resize(tmp.length());
	thrshld.resize(tmp.length());
	int q = 0;
	double sigmaMax = 128 / 255.;
	for (int j = p; j < heightR; j++) {
		for (int i = p; i < widthR; i++) {
			double Imin = 300, Imax = -1, c;
			for (int jj = j - p; jj <= j + p; jj++) {
				for (int ii = i - p; ii <= i + p; ii++)
					if (pow(i - ii, 2) + pow(j - jj, 2) <= r2) {
						if (tmp[jj * widthR + ii] < Imin)
							Imin = tmp.at(jj * widthR + ii);
						if (tmp[jj * widthR + ii] > Imax)
							Imax = tmp.at(jj * widthR + ii);
					}
				}
			cont[j * widthR + i] = Imax - Imin;
			if (cont[j * widthR + i] >= cmin)
				thrshld[j * widthR + i] = tmp1[j * widthR + i] * (1 + 0.18*((tmp2[j * widthR + i] / sigmaMax) - 1));
			else
				thrshld[j * widthR + i] = q;
		}
	}

	for (int j = 0; j < heightR; j++) {
		for (int i = 0; i < widthR; i++) {
			if (cont[j * widthR + i] < cmin) {
				if (thrshld[j * widthR + i] < cmin)
					tmp[j * widthR + i] = 0;
				else
					tmp[j * widthR + i] = 255;
			}
			else {
				if (tmp[j * widthR + i] < thrshld[j * widthR + i])
					tmp[j * widthR + i] = 0;
				else  tmp[j * widthR + i] = 255;
			}
		}
	}
	tmp = antireflection(tmp);
	return tmp;
}

void filters::tmp_save(QString fileName, QVector<double> data, int w, int h) {
	QFile outputFile(fileName);
	outputFile.open(QIODevice::WriteOnly);
	if (!outputFile.isOpen())
		return;

	QTextStream stream(&outputFile);
	stream << "P2" << endl;
	stream << w << " " << h << endl;
	stream << 255 << endl;

	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			stream << (int)data.at(j * w + i) << " ";
		}
		stream << endl;
	}

	outputFile.close();
}
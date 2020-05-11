#include "subWin.h"

subWin::subWin(QString fname) {
	fileName = fname;
	howManySubsurf = 1;
	sigmaSubsurf = 1.;
	tauSubsurf = 1.;
	kSubsurf = 1000.;
	niblackTimeStep = 5.;
	niblackMask = 3;
	bernsenMask = 2;
	numCont3D = 10;
	contourZCon = -1;
	heatEqTS = 1.0;
	cutDataAt = -8;
	sauvolaTimeStep = 1.;
	sauvolaMask = 3;
	NBaBrenTimeStep = 1.;
	NBaBrenMask = 3;
	SaBrenTimeStep = 1.;
	SaBrenMask = 3;
}

subWin::~subWin() {

}

void subWin::changeSubsurfParam(int howMany, double sigma, double tau, double k) {
	howManySubsurf = howMany;
	sigmaSubsurf = sigma;
	tauSubsurf = tau;
	kSubsurf = k;
}

void subWin::changeNiblackParam(double sigma, double mask) {
	niblackTimeStep = sigma;
	niblackMask = mask;
}

void subWin::changeBernsenParam(int mask) {
	bernsenMask = mask;
}

void subWin::changeNumberOfCont3D(int howMany) {
	numCont3D = howMany;
}

void subWin::changeZValOfCont3D(double z) {
	contourZCon = z;
}

void subWin::changeheatEqParam(double sigma) {
	heatEqTS = sigma;
}

void subWin::changecutDataAtVal(double z) {
	cutDataAt = z;
}

void subWin::changeSauvolaParam(double sigma, double mask) {
	sauvolaTimeStep = sigma;
	sauvolaMask = mask;
}

void subWin::changeHybNBaBParam(double sigma, double mask) {
	NBaBrenTimeStep = sigma;
	NBaBrenMask = mask;
}

void subWin::changeHybSaBParam(double sigma, double mask) {
	SaBrenTimeStep = sigma;
	SaBrenMask = mask;
}

void subWin::addFileName(QString name) {
	fileName = name;
}

void subWin::addHistInfo(QString info) {
	histInfo = info;
}

void subWin::add3DData(QString data) {
	Data3D << data;
}

void subWin::add2DData(QString data) {
	Data2D << data;
}

void subWin::remove3DData(int i) {
	Data3D.removeAt(i);
}

void subWin::remove2DData(int i) {
	Data2D.removeAt(i);
}

void subWin::setSelectedItem(QTreeWidgetItem p, int i) {
	parent = p;
	currentIndex = i;
}
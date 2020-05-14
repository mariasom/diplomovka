#pragma once

#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>

class subWin {
protected:

	QString fileName;		//win Param
	QStringList Data2D;
	QStringList Data3D;
	QString histInfo;
	int parent;
	int currentIndex;

	int howManySubsurf;		// subsurf param 
	double sigmaSubsurf;
	double tauSubsurf;
	double kSubsurf;
	double niblackTimeStep;  // niblack param
	int niblackMask;
	int bernsenMask;		// bernsen param
	double sauvolaTimeStep; // sauvola
	int sauvolaMask;
	double NBaBrenTimeStep; // niblack a Bren
	int NBaBrenMask;
	double SaBrenTimeStep; // niblack a Bren
	int SaBrenMask;
	int numCont3D; 	//contours 
	double contourZCon; 	//contour val
	double 	heatEqTS;	// heatEq
	double	cutDataAt; 	// cut at

public:
	subWin(QString fname);
	~subWin();

	int getHowManySubsurf() { return howManySubsurf; };
	double getSigmaSubsurf() { return sigmaSubsurf; };
	double getTauSubsurf() { return tauSubsurf; };
	double getKSubsurf() { return kSubsurf; };
	double getNBTimeStep() { return niblackTimeStep; };
	int getNBMask() { return niblackMask; };
	int getBernsenMask() { return bernsenMask; };
	double getSTimeStep() { return sauvolaTimeStep; };
	int getSMask() { return sauvolaMask; };
	double getHybNBBTimeStep() { return NBaBrenTimeStep; };
	int getHybNBBMask() { return NBaBrenMask; };
	double getHybSBTimeStep() { return SaBrenTimeStep; };
	int getHybSBMask() { return SaBrenMask; };
	int getnumCont3D() { return numCont3D; };
	double getcontourZCon() { return contourZCon; };
	double getheatEqTS() { return heatEqTS; };
	double getcutDataAt() { return cutDataAt; };
	QString getFileName() { return fileName; };
	QString get2DDataItem(int index) { return Data2D.at(index); };
	QString get3DDataItem(int index) { return Data3D.at(index); };
	QString getHistText() { return histInfo; };
	int getCurrentParent() { return parent; };
	int getCurrentIndex() { return currentIndex; };

	void changeSubsurfParam(int howMany, double sigma, double tau, double K);
	void changeNiblackParam(double sigma, double mask);
	void changeBernsenParam(int mask);
	void changeSauvolaParam(double sigma, double mask);
	void changeHybNBaBParam(double sigma, double mask);
	void changeHybSaBParam(double sigma, double mask);
	void changeNumberOfCont3D(int howMany);
	void changeZValOfCont3D(double z);
	void changeheatEqParam(double sigma);
	void changecutDataAtVal(double z);
	void addFileName(QString name);
	void addHistInfo(QString info);
	void add3DData(QString data);
	void add2DData(QString data);
	void remove3DData(int i);
	void remove2DData(int i);
	void setSelectedItem(int p,int i);
};

#include "source.h"

source::source()
{

}

source::~source()
{

}

void source::load(QString path) 
{
	QFile inputFile(path);
	inputFile.open(QIODevice::ReadOnly);
	if (!inputFile.isOpen())
	{
		return;
	}
	// read whole file
	QString wholeFile = inputFile.readAll();
	QStringList file = wholeFile.split(' '/*, QString::SkipEmptyParts*/);
	// load header
	QString fileType = file[0];
	// width and height
	cout << file.length() << endl;
	width = file[1].toInt();
	height = file[2].toInt();
	if (file[3].contains(".pgm", Qt::CaseSensitive)) {
		fileName = file[3];
		maxCol = file[4].toInt();
		// remove header
		for (int i = 0; i <= 4; i++)
			file.removeAt(i);
	}
	else {
		fileName = getFileName(path);
		maxCol = file[3].toInt();
		// remove header
		for (int i = 0; i <= 3; i++)
			file.removeAt(i);
	}

	// urcime typ pgm
	if (fileType.contains("P2", Qt::CaseSensitive)) {
		cout << "ascii file loading..." << endl;
		readAscii(file);
	}
	else if (fileType.contains("P5", Qt::CaseSensitive)) {
		readBinary(file);
		cout << "binary file loading..." << endl;
	}
	else
		return;
	
}

void source::readAscii(QStringList file) {


	cout << file[0].toStdString() << endl;
	
	/*for (int i = 0; i < file.length(); i++) {
		cout << file[i].toStdString() << endl;
	}*/

}

void source::readBinary(QStringList file) {
	cout << "tu sa nachadzam" << endl;

}

QString source::getFileName(QString path) {
	QStringList filePath;
	QString name;
	filePath = path.split('/');
	name = filePath.takeLast();
	return name;
}

#include "source.h"

source::source() {
	points = vtkSmartPointer<vtkPoints>::New();
	polydata = vtkSmartPointer<vtkPolyData>::New();
	colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	image = vtkSmartPointer<vtkImageData>::New();
}

source::~source()
{
	points->Delete();
	data.clear();
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
	inputFile.close();
	file = wholeFile.split(QRegExp("\\s+"), QString::SkipEmptyParts);

	// load header
	QString fileType = file[0];
	// width and height
	width = file[1].toInt();
	height = file[2].toInt();

	if (file[3].contains(".pgm", Qt::CaseSensitive)) {
		fileName = file[3];
		maxCol = file[4].toInt();
		// remove header
		for (int i = 0; i <= 4; i++) {
			file.removeAt(0);
		}
	}
	else {
		fileName = getFileName(path);
		maxCol = file[3].toInt();
		for (int i = 0; i <= 3; i++) {
			file.removeAt(0);
		}

		data.resize(file.length());
		for (int i = 0; i < file.length(); i++) {
			data[i] = file[i].toInt();
		}
	}

	// urcime typ pgm
	/*if (fileType.contains("P2", Qt::CaseSensitive)) {
//		cout << "ascii file loading..." << endl;
//		readAscii(file);
	}
	else if (fileType.contains("P5", Qt::CaseSensitive)) {
//		readBinary(file);
//		cout << "binary file loading..." << endl;
	}
	else
		return;*/
	
}

QString source::getFileName(QString path) {
	QStringList filePath;
	QString name;
	filePath = path.split('/');
	name = filePath.takeLast();
	return name;
}

void source::setPoints() {
	image->SetDimensions(width, height, 1);
	image->SetOrigin(.5, .5, 0);
	image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i, j, 0));
			pixel[0] = (unsigned char)data[j * width + i];
			std::cout << data[j * width + i] << " ";
		}
		
		std::cout << endl;
	}

	image->Modified();
}
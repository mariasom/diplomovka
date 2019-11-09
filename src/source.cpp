#include "source.h"

source::source() {
	points = vtkSmartPointer<vtkPoints>::New();
	//polydata = vtkSmartPointer<vtkPolyData>::New();
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

	sLength = 0;
	bool ok;
	QFile inputFile(path);
	inputFile.open(QIODevice::ReadOnly);
	if (!inputFile.isOpen())
	{
		return;
	}
	// read whole file
	QTextStream stream(&inputFile);
	QString line;
	//inputFile.close();
	//file = wholeFile.split(QRegExp("\\s+"), QString::SkipEmptyParts);

	// load header
	QString fileType = stream.readLine();
	sLength = fileType.length();
	sSize = fileType.size();

	// width and height
	line = stream.readLine();
	sLength += line.length();
	sSize += line.size();
	QStringList sList = line.split(' ', QString::SkipEmptyParts);
	width = sList[0].toInt();
	height = sList[1].toInt();

	line = stream.readLine();
	sLength += line.length();
	sSize += line.size();
	std::cout << sLength << std::endl;
	if (!line.contains(".pgm", Qt::CaseSensitive)) {
		fileName = getFileName(path);
		maxCol = line.toInt();	
	}
	else {
		fileName = line;
		sLength += fileName.length();
		line = stream.readLine();
		maxCol = line.toInt();
		sLength += fileName.length();
		std::cout << sLength << std::endl;
	}
	inputFile.close();

	//data.resize(file.length());
	// urcime typ pgm a podla toho priradim hodnoty
	if (fileType.contains("P2", Qt::CaseSensitive)) {
		std::cout << "ascii file loading..." << std::endl;
		readAscii(path);
	}
	else if (fileType.contains("P5", Qt::CaseSensitive)) {
		cout << "binary file loading..." << endl;
		binary = true;
		readBinary(path);
	}
	else
		return;

}

void source::readAscii(QString path) {
	
	QFile file(path);
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen())
	{
		return;
	}
	QTextStream input(&file);
	input.seek(sLength);
	QString wholeFile = input.readAll();
	QStringList splt = wholeFile.split(QRegExp("\\s+"), QString::SkipEmptyParts);

	data.resize(splt.length());
	std::cout << splt.length() << std::endl;
	for (int i = 0; i < splt.length(); i++) {
		data[i] = (unsigned char)splt[i].toInt();
	}
	  
	file.close();
}

void source::readBinary(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen())
	{
		return;
	}
	QTextStream input(&file);

	std::cout << sLength << std::endl;
	QVector<unsigned char> u;
	input.seek(sLength);
	QByteArray bytes = file.read(width * height * sizeof(unsigned char));
	u.resize(bytes.size());
	std::memcpy(u.data(), bytes.constData(), bytes.size());
	data.reserve(width*height);
	data = u;
	
	file.close();
}

QString source::getFileName(QString path) {
	QStringList filePath;
	QString name;
	filePath = path.split('/');
	name = filePath.takeLast();
	return name;
}

void source::setPoints() {

	// cez body

	/*points->SetNumberOfPoints(width*height);
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			points->SetPoint(j * width + i, i, j,0);
		}

	vtkSmartPointer<vtkPolyData> pointsPolydata =
		vtkSmartPointer<vtkPolyData>::New();

	pointsPolydata->SetPoints(points);

	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter->SetInputData(pointsPolydata);
	vertexFilter->Update();

	polydata->ShallowCopy(vertexFilter->GetOutput());

	vtkSmartPointer<vtkUnsignedCharArray> color =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	color->SetNumberOfValues(width*height);

	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			 color->SetValue(j * width + i,(unsigned char)data[j * width + i]);
			 std::cout << color->GetValue(j * width + i) << " ";
		}
		std::cout << std::endl;
	}
	
	polydata->GetPointData()->SetScalars(color);
	polydata->Modified();*/

	image->SetDimensions(width, height, 1);
	image->SetOrigin(.5, .5, 0);
	image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
	
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i, j, 0));
			pixel[0] = (unsigned char)data[j * width + i];
			// std::cout << data[j * width + i] << " ";
		}
		
		std::cout << endl;
	}

	image->Modified();
}
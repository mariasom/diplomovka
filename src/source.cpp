#include "source.h"

source::source() {
	points = vtkSmartPointer<vtkPoints>::New();
	polydata = vtkSmartPointer<vtkPolyData>::New();
	colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	image = vtkSmartPointer<vtkImageData>::New();
	polydata2D = vtkSmartPointer<vtkPolyData>::New();
}

source::~source()
{
	points->Delete();
	dataFilt.clear();
	data3DFilt.clear();
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
	std::cout << line.toStdString() << endl;

	// width and height or comment
	line = stream.readLine();
	sLength += line.length();
	sSize += line.size();
	std::cout << line.toStdString() << endl;
	if (line.contains('#')) {	//line is comment
		line = line = stream.readLine();
		sLength += line.length();
		sSize += line.size();
		std::cout << line.toStdString() << endl;
	}
	QStringList sList = line.split(' ', QString::SkipEmptyParts);
	width = sList[0].toInt();
	height = sList[1].toInt();

	line = stream.readLine();
	sLength += line.length();
	sSize += line.size();
	std::cout << line.toStdString() << endl;
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

	addFiltData(data);
	data.clear();
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
		std::cout << (int)data[i] << " ";
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

	//std::cout << sLength << std::endl;
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

void source::setPoints(QVector<unsigned char> &setData, int p) {

	// cez body

	/*int widthR = width + 2 * p;
	int heightR = height + 2 * p;

	points->SetNumberOfPoints(widthR*heightR);
	for (int j = 0; j < heightR; j++)
		for (int i = 0; i < widthR; i++) {
			points->SetPoint(j * widthR + i, i, j,0);
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
	color->SetNumberOfValues(widthR*heightR);

	for (int j = 0; j < widthR; j++)
	{
		for (int i = 0; i < heightR; i++)
		{
			 color->SetValue(j * widthR + i,(unsigned char)data[j * widthR + i]);
			 std::cout << (int)color->GetValue(j * widthR + i) << " ";
		}
		std::cout << std::endl;
	}

	polydata2D->GetPointData()->SetScalars(color);
	polydata2D->Modified();*/

	int widthR = width + 2 * p;
	int heightR = height + 2 * p;

	image->SetDimensions(widthR, heightR, 1);
	image->SetOrigin(.5, .5, 0);
	//image->SetSpacing(widthR, heightR, widthR*heightR);
	image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

	for (int j = 0; j < widthR; j++)
	{
		for (int i = 0; i < heightR; i++)
		{
			unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i, j, 0));
			pixel[0] = (unsigned char)setData[j * widthR + i];
		}
	}
	image->Modified();
}

void source::addFiltData(QVector<unsigned char> &addData) {
	dataFilt.resize(dataFilt.size() + 1);
	dataFilt[dataFilt.size() - 1] = addData;
}

void source::add3DData(QVector<double> &addData) {
	data3DFilt.resize(data3DFilt.size() + 1);
	data3DFilt[data3DFilt.size() - 1] = addData;
}

void source::save_ascii(QString fileName, int index) {

	QFile outputFile(fileName);
	outputFile.open(QIODevice::WriteOnly);
	if (!outputFile.isOpen())
		return;

	QTextStream stream(&outputFile);
	stream << "P2" << endl;
	stream << width << " " << height << endl;
	stream << maxCol << endl;

	//for (int j = 0; j < dataFilt.at(index).size(); j++) {
	//	stream << dataFilt.at(index).at(j) << endl;
	//}

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			stream << dataFilt.at(index).at(j * width + i) <<  " ";
		}
		stream << endl;
	}
	outputFile.close();
}

void source::create3Ddata(QVector<double> z) {
	int widthR, heightR;
	int p = 1;
	//widthR = width + 2 * p;
	//heightR = height + 2 * p;

	points->SetNumberOfPoints(width*height);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			points->SetPoint(j * width + i, i, j, z[width * j + i]);
		}

	//vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

	//for (int i = 0; i < points->GetNumberOfPoints(); ++i)
	//{
	//	vtkIdType id[1];
	//	id[0] = i;
	//	vertices->InsertNextCell(1, id);
	//}

	vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();

	for (int j = 0; j < height - 1; j++)
		for (int i = 0; i < width - 1 ; i++)
		{
			triangle->GetPointIds()->SetId(0, j * width + i);
			triangle->GetPointIds()->SetId(1, (j + 1) * width + i);
			triangle->GetPointIds()->SetId(2, (j + 1) * width + (i + 1));
			triangles->InsertNextCell(triangle);

			triangle->GetPointIds()->SetId(0, j * width + i);
			triangle->GetPointIds()->SetId(1, (j + 1) * width + (i + 1));
			triangle->GetPointIds()->SetId(2, (j)* width + (i + 1));
			triangles->InsertNextCell(triangle);
		}

	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();

/*	vtkSmartPointer<vtkFloatArray> scalars =
		vtkSmartPointer<vtkFloatArray>::New();
	scalars->SetNumberOfTuples(points->GetNumberOfPoints());
	double bounds[6];
    points->GetBounds(bounds);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++)
		{
			if((bounds[5] - bounds[4])/2 < z[width * j + i])
				scalars->SetTuple1(j * width + i, 0);
			else
				scalars->SetTuple1(j * width + i, 50);
			std::cout << abs(points->GetBounds()[4]) + z[width * j + i] << " ";
		}
		std::cout << endl;
	}*/

	polydata->SetPoints(points);
	// polydata->GetPointData()->SetScalars(scalars);
	//polydata->SetVerts(vertices);
	polydata->SetStrips(triangles);
	colorPolyData();
}

void source::colorPolyData() {
	colors->SetNumberOfComponents(3);
	colors->SetName("Colors");
	colors->SetNumberOfTuples(polydata->GetNumberOfPoints());
	double bounds[6];
	polydata->GetBounds(bounds);
	colorLookupTable->SetTableRange(bounds[4], bounds[5]);
	colorLookupTable->Build();

	// Generate the colors for each point based on the color map
	unsigned char colore[3];
	double *tmpColor;
	vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();

	color->AddRGBPoint(0.0, 0.0, 0.0, 0.5);
	color->AddRGBPoint(0.1, 0.0, 0.0, 1.0);
	color->AddRGBPoint(0.35, 0.0, 1.0, 1.0);
	color->AddRGBPoint(0.65, 1.0, 1.0, 0.0);
	color->AddRGBPoint(0.9, 1.0, 0.0, 0.0);
	color->AddRGBPoint(1.0, 0.5, 0.0, 0.0);

	for (int i = 0; i < polydata->GetNumberOfPoints(); i++) {
		double colora;
		double p[3];
		polydata->GetPoint(i, p);
		colora = /*1 -*/ ((p[2] - bounds[4]) / (bounds[5] - bounds[4]));
		tmpColor = color->GetColor(colora);
		colore[0] = tmpColor[0] * 255;
		colore[1] = tmpColor[1] * 255;
		colore[2] = tmpColor[2] * 255;
		colors->SetTypedTuple(i, colore);
	}

	int maxCol = 255;
	for (int i = 0; i <= maxCol; i++)
	{
		double *rgb;
		rgb = color->GetColor(static_cast<double>(i) / maxCol);
		colorLookupTable->SetTableValue(i, rgb);
	}

	polydata->GetPointData()->SetScalars(colors);
	polydata->Modified();
}

void source::displayOnPlane(vtkSmartPointer<vtkPolyData> data) {
	
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			points->SetPoint(j * width + i, i, j, 0 );
		}


}

void source::saveVtk(QString fileName, int index, bool binary) {
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	create3Ddata(get3DData(index));
	QByteArray ba = fileName.toLocal8Bit();
	const char *cstr = ba.data();
	writer->SetFileName(cstr);
	writer->SetInputData(polydata);

	if(binary)
		writer->SetDataModeToBinary();
	else
		writer->SetDataModeToAscii();

	writer->Write();
}
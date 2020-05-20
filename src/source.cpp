#include "source.h"

source::source() {
	points2D = vtkSmartPointer<vtkPoints>::New();
	points3D = vtkSmartPointer<vtkPoints>::New();
	polydata = vtkSmartPointer<vtkPolyData>::New();
	colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	polydata2D = vtkSmartPointer<vtkPolyData>::New();

	// test
	imageDataGeometryFilter =
		vtkSmartPointer<vtkImageDataGeometryFilter>::New();
}

source::~source() {
	points2D->Delete();
	polydata2D->Delete();
	dataFilt.clear();
	if (!data3DFilt.isEmpty()) {
		data3DFilt.clear();
		colors->Delete();
		colorLookupTable->Delete();
		points3D->Delete();
		polydata->Delete();
	}
}

void source::load(QString path) {
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
	QString line, tmpstring;

	// load header
	QString fileType = stream.readLine();
	tmpstring = fileType + "\n";
	sLength += tmpstring.length();

	// width and height or comment
	line = stream.readLine();
	tmpstring = line + "\n";
	sLength += tmpstring.length();
	sSize += line.size();
	
	if (line.contains('#')) {	//line is comment
		line = line = stream.readLine();
		tmpstring = line + "\n";
		sLength += tmpstring.length();
	}
	QStringList sList = line.split(' ', QString::SkipEmptyParts);
	width = sList[0].toInt();
	height = sList[1].toInt();
	
	line = stream.readLine();
	tmpstring = line + "\n";
	sLength += tmpstring.length();
	sSize += line.size();
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

	// urcime typ pgm a podla toho priradim hodnoty
	if (fileType.contains("P2", Qt::CaseSensitive)) {
		setText("ascii portable graymap (.pgm)");
		readAscii(path);
	}
	else if (fileType.contains("P5", Qt::CaseSensitive)) {
		setText("binary portable graymap  (.pgm)");
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
	}
	file.close();
}

void source::readBinary(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen()) {
		return;
	}
	QTextStream input(&file);

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
	int widthR = width + 2 * p;
	int heightR = height + 2 * p;

	points2D->SetNumberOfPoints(width*height);
	for (int j = 0; j < height; j++)
		for (int i = 0; i < widthR; i++) {
			points2D->SetPoint(j * width + i, i, j,0);
		}

	vtkSmartPointer<vtkPolyData> pointsPolydata =
		vtkSmartPointer<vtkPolyData>::New();
	pointsPolydata->SetPoints(points2D);
	
	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter->SetInputData(pointsPolydata);
	vertexFilter->Update();

	polydata2D->ShallowCopy(vertexFilter->GetOutput());

	vtkSmartPointer<vtkCellArray> polygons =
		vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkPolygon> polygon = 
		vtkSmartPointer<vtkPolygon>::New();

	for (int j = 0; j < height - 1; j++)
		for (int i = 0; i < width - 1; i++) {
			polygon->GetPointIds()->SetNumberOfIds(4); 
			polygon->GetPointIds()->SetId(0, j * width + i);
			polygon->GetPointIds()->SetId(1, (j + 1) * width + i);
			polygon->GetPointIds()->SetId(2, (j + 1) * width + (i + 1));
			polygon->GetPointIds()->SetId(3, j * width + (i + 1));
			polygons->InsertNextCell(polygon);
		}

	vtkSmartPointer<vtkUnsignedCharArray> color = 
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	color->SetNumberOfValues(widthR*heightR);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			 color->SetValue(j * width + i,(unsigned char)setData[j * widthR + i]);
		}

	polydata2D->GetPointData()->SetScalars(color);
	polydata2D->SetPolys(polygons);
	polydata2D->Modified();
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

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			stream << dataFilt.at(index).at(j * width + i) <<  " ";
		}
		stream << endl;
	}
	outputFile.close();
}

void source::create3Ddata(QVector<double> z) {
	int widthR, heightR;
	int p = 1;

	points3D->SetNumberOfPoints(width*height);

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			points3D->SetPoint(j * width + i, i, j, z[width * j + i]);
		}

	vtkSmartPointer<vtkCellArray> polygons =
		vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkPolygon> polygon =
		vtkSmartPointer<vtkPolygon>::New();

	for (int j = 0; j < height - 1; j++)
		for (int i = 0; i < width - 1; i++) {
			polygon->GetPointIds()->SetNumberOfIds(4);
			polygon->GetPointIds()->SetId(0, j * width + i);
			polygon->GetPointIds()->SetId(1, (j + 1) * width + i);
			polygon->GetPointIds()->SetId(2, (j + 1) * width + (i + 1));
			polygon->GetPointIds()->SetId(3, j * width + (i + 1));
			polygons->InsertNextCell(polygon);
		}

	polydata->SetPoints(points3D);
	polydata->SetPolys(polygons);
	addZMinandMax();
}

void source::setCol(vtkSmartPointer<vtkColorTransferFunction> transferF,int colorIndex) {

	if (colorIndex == 0) { // black&white //blue&red
		transferF->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
		transferF->AddRGBPoint(1.0, 1, 1, 1);
	}
	else if (colorIndex == 1) { // colorfull
		transferF->AddRGBPoint(0.0, 0.0, 0.0, 0.5);
		transferF->AddRGBPoint(0.1, 0.0, 0.0, 1.0);
		transferF->AddRGBPoint(0.35, 0.0, 1.0, 1.0);
		transferF->AddRGBPoint(0.65, 1.0, 1.0, 0.0);
		transferF->AddRGBPoint(0.9, 1.0, 0.0, 0.0);
		transferF->AddRGBPoint(1.0, 0.5, 0.0, 0.0);
	}
}

void source::colorPolyData(int colorIndex) {
	colors->SetNumberOfComponents(3);
	colors->SetName("Colors");
	colors->SetNumberOfTuples(polydata->GetNumberOfPoints());
	polydata->GetBounds(bounds);
	colorLookupTable->SetTableRange(bounds[4], bounds[5]);
	colorLookupTable->Build();

	unsigned char colore[3];
	double *tmpColor;
	vtkSmartPointer<vtkColorTransferFunction> color = 
		vtkSmartPointer<vtkColorTransferFunction>::New();

	setCol(color, colorIndex);

	for (int i = 0; i < polydata->GetNumberOfPoints(); i++) {
		double colora;
		double p[3];
		polydata->GetPoint(i, p);
		colora = ((p[2] - bounds[4]) / (bounds[5] - bounds[4]));
		tmpColor = color->GetColor(colora);
		colore[0] = tmpColor[0] * 255;
		colore[1] = tmpColor[1] * 255;
		colore[2] = tmpColor[2] * 255;
		colors->SetTypedTuple(i, colore);
	}

	int maxCol = 255;
	for (int i = 0; i <= maxCol; i++) {
		double *rgb;
		rgb = color->GetColor(static_cast<double>(i) / maxCol);
		colorLookupTable->SetTableValue(i, rgb);
	}

	polydata->GetPointData()->SetScalars(colors);
	polydata->Modified();
}

void source::saveVtk3D(QString fileName, int index, bool binary) {
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
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

void source::saveVtk2D(QString fileName, int index, bool binary) {
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	setPoints(getFiltData(index));
	QByteArray ba = fileName.toLocal8Bit();
	const char *cstr = ba.data();
	writer->SetFileName(cstr);
	writer->SetInputData(polydata2D);

	if (binary)
		writer->SetDataModeToBinary();
	else
		writer->SetDataModeToAscii();
	writer->Write();
}

void source::addZMinandMax() {
	polydata->GetBounds(bounds);
	zMax.resize(zMax.size() + 1);
	zMin.resize(zMin.size() + 1);
	zMax[zMax.size() - 1] = bounds[5];
	zMin[zMin.size() - 1] = bounds[4];
	setText("Z min: " + QString::number(bounds[4]) + " Z max: " + QString::number(bounds[5]));
}

void source::saveHistOutput(QString text, QString fileName) {

	QFile outputFile(fileName);
	outputFile.open(QIODevice::WriteOnly);
	if (!outputFile.isOpen())
		return;
	QTextStream stream(&outputFile);
	stream << text;
	outputFile.close();
}

void source::readTifFile(QString path) {
	vtkSmartPointer<vtkTIFFReader> reader =
		vtkSmartPointer<vtkTIFFReader>::New();
	QByteArray ba = path.toLocal8Bit();
	const char *cstr = ba.data();
	reader->SetNumberOfScalarComponents(1);
	reader->SetFileName(cstr);
	reader->Update();
	std::cout << reader->GetNumberOfOutputPorts();
	int bound[6];
	reader->GetOutput()->GetExtent(bound);
	imageDataGeometryFilter->SetInputConnection(reader->GetOutputPort());
	imageDataGeometryFilter->Update();

	vtkSmartPointer<vtkPolyData> tmppoly = 
		vtkSmartPointer<vtkPolyData>::New();

	tmppoly = imageDataGeometryFilter->GetOutput();
	tmppoly->Modified();
	
	width = bound[1] + 1;
	height = bound[3] + 1;
	vtkSmartPointer<vtkDataArray> array = vtkSmartPointer<vtkUnsignedCharArray>::New();
	array = tmppoly->GetPointData()->GetScalars();

	QVector<unsigned char> data;
	data.resize(tmppoly->GetNumberOfPoints());
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			data[j*width + i] = (int)(array->GetTuple(j*width + i)[1]);
		}

	setText("Tagged Image File Format (.tif)");
	addFiltData(data);
}

void source::setNewDataWin(QVector<unsigned char> data, int h, int w) {
	height = h;
	width = w;

	addFiltData(data);
}

void source::setText(QString text) {
	info = text;
}

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
	// cout << fileType.toStdString();
	// width and height
	width = file[1].toInt();
	cout << width;
	height = file[2].toInt();
	cout << height;
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
			//cout << file[0].toStdString();
			file.removeAt(0);
		}

		data.resize(file.length());
		for (int i = 0; i < file.length(); i++) {
			data[i] = file[i].toInt();
		}
		// cout << "dlzka: " << file.length();
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

/*void source::readAscii(QStringList file) {


	// cout << file[0].toStdString() << endl;
	
	for (int i = 0; i < file.length(); i++) {
		cout << file[i].toStdString() << '\t';
	}

}

void source::readBinary(QStringList file) {
//	cout << "tu sa nachadzam" << endl;

}*/

QString source::getFileName(QString path) {
	QStringList filePath;
	QString name;
	filePath = path.split('/');
	name = filePath.takeLast();
	return name;
}

/*void source::setPoints() {

	// setting points
	points->SetNumberOfPoints(width*height);

	std::cout << "pocet bodov: " << points->GetNumberOfPoints() << std::endl;
	std::cout << "sirka: " << width << std::endl;
	std::cout << "vyska: " << height << std::endl;
	// cout << width << endl;
	// cout << height << endl;

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			points->SetPoint(j * width + i, i, j, 0);
		}

	// setting polydata
	polydata->SetPoints(points);

	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter->SetInputData(pointsPolydata);
	vertexFilter->Update();

	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->ShallowCopy(vertexFilter->GetOutput());

	// Setup colors
	vtkSmartPointer<vtkNamedColors> namedColors =
		vtkSmartPointer<vtkNamedColors>::New();

	vtkSmartPointer<vtkUnsignedCharArray> colors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	colors->SetNumberOfComponents(3);
	colors->SetName("Colors");
	colors->InsertNextTupleValue(namedColors->GetColor3ub("Tomato").GetData());
	colors->InsertNextTupleValue(namedColors->GetColor3ub("Mint").GetData());
	colors->InsertNextTupleValue(namedColors->GetColor3ub("Peacock").GetData());

	polydata->GetPointData()->SetScalars(colors);

	// setting color  initial color
	colors->SetNumberOfComponents(1);
	colors->SetName("Colors");
	colors->SetNumberOfTuples(width*height);


	/*for (int i = 0; i < data.length(); i++)
	{
		double colora;
		colora = /*1 -*//* ((dataToColor[i] - tmpmin) / (tmpmax - tmpmin));

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
		//hueLut->SetTableValue(i, rgb);
		colorLookupTable->SetTableValue(i, rgb);
	}

	polydata->GetPointData()->SetScalars(colors);
	polydata->Modified();*/

	/*vtkSmartPointer<vtkImageData> image =
		vtkSmartPointer<vtkImageData>::New();
	int imageExtent[6] = { 0, 15, 0, 15, 0, 0 };
	image->SetExtent(imageExtent);
#if VTK_MAJOR_VERSION <= 5
	image->SetNumberOfScalarComponents(1);
	image->SetScalarTypeToDouble();
#else
	image->AllocateScalars(VTK_DOUBLE, 1);
#endif

	double scalarvalue = 0.0;

	for (int y = imageExtent[2]; y <= imageExtent[3]; y++)
	{
		for (int x = imageExtent[0]; x <= imageExtent[1]; x++)
		{
			double* pixel = static_cast<double*>(image->GetScalarPointer(x, y, 0));
			pixel[0] = scalarvalue;
			scalarvalue += 1.0;
		}
	}

	// Map the scalar values in the image to colors with a lookup table:
	vtkSmartPointer<vtkLookupTable> lookupTable =
		vtkSmartPointer<vtkLookupTable>::New();
	lookupTable->SetNumberOfTableValues(256);
	lookupTable->SetRange(0.0, 255.0);
	lookupTable->Build();

	// Pass the original image and the lookup table to a filter to create
	// a color image:
	scalarValuesToColors = vtkSmartPointer<vtkImageMapToColors>::New();
	scalarValuesToColors->SetLookupTable(lookupTable);
	scalarValuesToColors->PassAlphaToOutputOn();
#if VTK_MAJOR_VERSION <= 5
	scalarValuesToColors->SetInput(image);
#else
	scalarValuesToColors->SetInputData(image);
#endif

	vtkSmartPointer<vtkImageActor> imageActor =
		vtkSmartPointer<vtkImageActor>::New();
	imageActor->GetMapper()->SetInputConnection(
		scalarValuesToColors->GetOutputPort());
	imageActor->GetProperty()->SetInterpolationTypeToNearest();

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(imageActor);
	/*renderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);

	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	//return scalarValuesToColors;
}*/

//}

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
		}
	}

	image->Modified();
}
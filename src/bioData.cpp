#include "bioData.h"

bioData::bioData() {
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	QFont f("Times New Roman", 10, QFont::Normal);

	QScrollArea* VerticalScrollArea = new QScrollArea;
	VerticalScrollArea->setWidgetResizable(true);
	QWidget* contentWidget = new QWidget;
	VerticalScrollArea->setWidget(contentWidget);
	QGridLayout* gridScrollArea = new QGridLayout(contentWidget);
	VerticalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
}

/*void bioData::slotExit() 
{
	qApp->exit(); 
}
*/

void bioData::actionOpenFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));
	_vData->load(fileName);
	
	// cout << fileName.toStdString() << endl;
	// QFile inputFile(fileName);
	// inputFile.open(QIODevice::ReadOnly);
	// if (!inputFile.isOpen())
	// {
	//	return;
	// }
	// p2
	// QString wholeFile = inputFile.readAll();
	// cout << wholeFile.toStdString();
	// width & height
	/*QString line = inputFile.readLine();
	// cout << line.toStdString();
	QStringList prop = line.split(' ');
	// cout << prop.length();
	int width = prop[1].toInt();
	int heigth = prop[2].toInt();
	QString col = inputFile.readLine();
	int colMax = col.toInt();

	QStringList split;
	for (int i = 0; i < width; i++) {
		line = inputFile.readLine();
		split = line.split(' ', QString::SkipEmptyParts);
		for (int j = 0; j < width; j++) {
			//cout << split[j].toInt() << " ";
		}
		//cout << endl;
	}*/
	
}

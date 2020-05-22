#include "help.h"

Help::Help(QHelpEngine* helpEngine, QWidget* parent) :QTextBrowser(parent), helpEngine(helpEngine) {
}

QVariant Help::loadResource(int type, const QUrl &name) {
	if (name.scheme() == "qthelp")
		return QVariant(helpEngine->fileData(name));
	else
		return QTextBrowser::loadResource(type, name);
}
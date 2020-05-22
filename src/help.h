#pragma once

#include <QTextBrowser>
#include <QHelpEngine>
#include <QDebug>

class Help : public QTextBrowser
{
public:
	Help(QHelpEngine* helpEngine, QWidget* parent = 0);
	QVariant loadResource(int type, const QUrl& name);
private:
	QHelpEngine* helpEngine;
};

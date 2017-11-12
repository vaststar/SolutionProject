#include "PluginFrame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PluginFrame w;
	w.show();
	return a.exec();
}

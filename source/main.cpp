#include "mainwindow.h"
#include <QApplication>

#include "SpecDatabase.h"

int main(int argc, char *argv[])
{
	SpecDatabase specDB;
    QApplication a(argc, argv);
    MainWindow w(specDB);
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("cleanlooks");
    MainWindow w;
    w.show();

    return a.exec();
}

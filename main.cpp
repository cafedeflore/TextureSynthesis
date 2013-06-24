#include <QtGui/QApplication>
#include <ANN.h>
#include "mainwindow.h"
#include "texture.h"
#include "imageConversion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}

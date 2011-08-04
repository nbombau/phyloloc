#include <QtGui/QApplication>
#include "PhyloGUI/inc/mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    PhyloGUI::MainWindow w;
    w.show();
    return a.exec();
}

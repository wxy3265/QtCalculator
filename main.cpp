#include "mainwindow.h"

#include <QApplication>

//modifed for Lab2 R3 step
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

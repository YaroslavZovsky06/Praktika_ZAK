#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("Determinant calculator",3);
    w.show();

    return a.exec();
}

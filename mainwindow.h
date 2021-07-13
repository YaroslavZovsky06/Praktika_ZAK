#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int row1, row2;
    int column1, column2;
    int arr1[99][99];
    int arr2[99][99];
    int res[99][99];


private slots:
    void determThisM();
public:
    int determinant(int size);
};
#endif // MAINWINDOW_H

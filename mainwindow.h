#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MainWindow(QString title, int n);

public slots:
   void calculateDeterminant(QLabel *label);
   void resizeDeterminantMatrix(QLineEdit* dim, QWidget *matrixFrame);
   private:
    Ui::MainWindow *ui;
    QWidget *central;
    QVector<QVector<QLineEdit*>> matrix;
    QGridLayout *grid;

    int n;

};

#endif // MAINWINDOW_H

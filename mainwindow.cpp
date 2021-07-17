#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Matrix.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    }

MainWindow::MainWindow(QString title, int n){

    setWindowTitle(title);
    this->n = n;


    QWidget *mainFrame = new QWidget(this); //рамка рабочей части
    QGridLayout *frameLayout = new QGridLayout(); //макет окна
    QWidget *central = new QWidget; //рамка окна
    central->setLayout(frameLayout); //задает окно макета сетки
    setCentralWidget(central); //установите фрейм как главный
    frameLayout->addWidget(mainFrame); //добавляет фрейм рабочей детали в Главное окно
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QStackedLayout *stackedLayout = new QStackedLayout; //макет стеки
    mainFrame->setLayout(mainLayout); //добавляет все операции с макетом и рамкой
    QWidget *determinat = new QWidget();

    stackedLayout->addWidget(determinat);
    QWidget *matrixFrame = new QWidget(determinat); //создание фрейма массива
    QVBoxLayout *determinatLayout = new QVBoxLayout;
    determinat->setLayout(determinatLayout);
    determinatLayout->addWidget(matrixFrame);
    mainLayout->addLayout(stackedLayout);


    QWidget *buttonpanel = new QWidget;
    QLabel *descr = new QLabel("Insert matrix dimension:");
    QLineEdit *dim = new QLineEdit();

    QPushButton *resize = new QPushButton("Resize");
    QPushButton *calc = new QPushButton("Calculate");
    dim->setFixedWidth(50);

    QHBoxLayout *buttonpanelLayout = new QHBoxLayout;
    QHBoxLayout *buttonpanelLayoutTop = new QHBoxLayout;
    QWidget *buttonpanelTop = new QWidget;
    buttonpanel->setLayout(buttonpanelLayout);
    buttonpanelLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonpanelLayout->addWidget(descr);
    buttonpanelLayout->addWidget(dim);
    buttonpanelLayout->addWidget(resize);
    buttonpanelLayout->addWidget(calc);
    buttonpanelTop->setLayout(buttonpanelLayoutTop);
    buttonpanelLayoutTop->addWidget(buttonpanel);


    dim->setText("3");
    grid = new QGridLayout();
    for(int i=0;i<n;i++){
        matrix.append(QVector<QLineEdit*>());
        for(int j=0;j<n;j++){
            matrix[i].append(new QLineEdit);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]->setFixedSize(30,30);
            matrix[i][j]->setText("0");
            matrix[i][j]->setAlignment(Qt::AlignCenter);
            grid->addWidget(matrix[i][j],i,j);
        }
    }
    grid->setSizeConstraint(QLayout::SetMaximumSize);
    QHBoxLayout *detCentralizer = new QHBoxLayout();
    matrixFrame->setLayout(detCentralizer);
    QWidget *subMatrixFrame = new QWidget();
    detCentralizer->addWidget(subMatrixFrame);
    subMatrixFrame->setLayout(grid);

    QWidget *theoryFrame = new QWidget;
    QHBoxLayout *theoryLayout = new QHBoxLayout;
    QLineEdit *theoryLine = new QLineEdit();
    theoryFrame->setLayout(theoryLayout);
    theoryLayout->addWidget(theoryLine);
    theoryLine->setFixedSize(400,200);
    theoryLine->setText("Тут должна быть теория");

    determinatLayout->addWidget(theoryFrame);

    QWidget *resultFrame = new QWidget;
    QHBoxLayout *resultLayout = new QHBoxLayout;
    QLabel *resultLabel = new QLabel("");
    resultFrame->setLayout(resultLayout);
    resultLayout->addWidget(resultLabel);

    determinatLayout->addWidget(buttonpanelTop);
    determinatLayout->addWidget(matrixFrame);
    determinatLayout->addWidget(resultFrame);

    this->connect(calc,&QPushButton::clicked,
        [this, resultLabel](){
            calculateDeterminant(resultLabel);
        }
    );

    this->connect(resize,&QPushButton::clicked,
        [this,dim,subMatrixFrame](){
            resizeDeterminantMatrix(dim,subMatrixFrame);
        }
    );




}

void MainWindow::calculateDeterminant(QLabel *label){
    Matrix m(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x = matrix.at(i).at(j)->text().toInt();
            m.setCell(i,j,x);
        }
    }
    int det = m.calculateRecursiveDeterminant();
    label->setText("Determinat: " + QString::number(det));
    label->setAlignment(Qt::AlignCenter);

}



void MainWindow::resizeDeterminantMatrix(QLineEdit* dim, QWidget *matrixFrame){
    int x = dim->text().toInt();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            delete matrix[i][j];
        }
    }
    matrix.clear();
    n = x;
    delete grid;
    grid = new QGridLayout();
    grid->setSizeConstraint(QLayout::SetMaximumSize);
    for(int i=0;i<n;i++){
        matrix.append(QVector<QLineEdit*>());
        for(int j=0;j<n;j++){
            matrix[i].append(new QLineEdit);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]->setFixedSize(30,30);
            matrix[i][j]->setText("0");
            matrix[i][j]->setAlignment(Qt::AlignCenter);
            grid->addWidget(matrix[i][j],i,j);
        }
    }
    matrixFrame->setLayout(grid);
    grid->update();
    matrixFrame->update();
}



MainWindow::~MainWindow(){
    delete ui;
}


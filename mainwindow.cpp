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
    QVBoxLayout *mainLayout = new QVBoxLayout;//выстраивает виджеты по вертикали
    QStackedLayout *stackedLayout = new QStackedLayout; //макет стеки
    mainFrame->setLayout(mainLayout); //добавляет все операции с макетом и рамкой
    QWidget *determinat = new QWidget();//создание окна вычисления определителя
    stackedLayout->addWidget(determinat);//добавляет виджеты окна
    QWidget *matrixFrame = new QWidget(determinat); //создание фрейма массива
    QVBoxLayout *determinatLayout = new QVBoxLayout;//выстраивает виджеты по вертикали
    determinat->setLayout(determinatLayout);//добавляет все операции с виджетами
    determinatLayout->addWidget(matrixFrame);//добавляетфрейм массива
    mainLayout->addLayout(stackedLayout);//добавляет макет


    QWidget *buttonpanel = new QWidget; //создание панели с вводом размерности матрицы и кнопками
    QLabel *descr = new QLabel("Insert matrix dimension:");//подпись перед вводом размерноси матрицы
    QLineEdit *dim = new QLineEdit();//создание поля для ввода размерности
    QPushButton *resize = new QPushButton("Resize");//кнопка которая создает матрицу нужной размерности
    QPushButton *calc = new QPushButton("Calculate");//кнопка которая вычисляет определитель
    dim->setFixedWidth(50);//размер поля для ввода размерности матрицы
    QHBoxLayout *buttonpanelLayout = new QHBoxLayout;//выстраивает панель горизонтально
    buttonpanel->setLayout(buttonpanelLayout);//добавляет все операции с панелью
    buttonpanelLayout->addWidget(descr);//добавляет лейбл
    buttonpanelLayout->addWidget(dim);//добавляет ввод размерности матрицы
    buttonpanelLayout->addWidget(resize);//добавляет кнопку изменить размерность
    buttonpanelLayout->addWidget(calc);//добавляет кногмку вычисления
    buttonpanel->setLayout(buttonpanelLayout);//создает панель
    buttonpanelLayout->addWidget(buttonpanel);//добавляет панель
    dim->setText("3");

    grid = new QGridLayout();//для создания сетки
    for(int i=0;i<n;i++){
        matrix.append(QVector<QLineEdit*>());
        for(int j=0;j<n;j++){
            matrix[i].append(new QLineEdit);
        }//создает матрицу заданного размера
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]->setFixedSize(30,30);//размерность ячеек матрицы
            matrix[i][j]->setText("0");
            matrix[i][j]->setAlignment(Qt::AlignCenter);//выравнивает текст по центру
            grid->addWidget(matrix[i][j],i,j);//добавляет матрицу в сетку
        }
    }
    grid->setSizeConstraint(QLayout::SetMaximumSize);//выравнивание сетки
    QHBoxLayout *detCentralizer = new QHBoxLayout();//выстраивает панель горизонтально
    matrixFrame->setLayout(detCentralizer);//добавляет все операции с матрицей
    QWidget *subMatrixFrame = new QWidget();//создает виджет матрицы
    subMatrixFrame->setLayout(grid);//добавляет созданную матрицу
    detCentralizer->addWidget(subMatrixFrame);//выводит матрицу
\

    QWidget *theoryFrame = new QWidget;//создаем панель с текстом
    QHBoxLayout *theoryLayout = new QHBoxLayout;//размещает панель горизонтально
    QLineEdit *theoryLine = new QLineEdit();//создаем место для текста
    theoryFrame->setLayout(theoryLayout);//добавляем панель с текстом
    theoryLayout->addWidget(theoryLine);//добавляем на панель виджет
    theoryLine->setText("Задаём размер матрицы, вводим данные и находим определитель.");
    determinatLayout->addWidget(theoryFrame);//выводит фрейм с текстом

    QWidget *resultFrame = new QWidget;//создается панель ответа
    QHBoxLayout *resultLayout = new QHBoxLayout;//размещает панель горизонтально
    QLabel *resultLabel = new QLabel("");//создается лейбл с ответом
    resultFrame->setLayout(resultLayout);//создает панель
    resultLayout->addWidget(resultLabel);//добавляет панель

    determinatLayout->addWidget(buttonpanel);//вывод панели кнопок
    determinatLayout->addWidget(matrixFrame);//вывод матрицы после панели
    determinatLayout->addWidget(resultFrame);//вывод результата

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
            int x = matrix.at(i).at(j)->text().toInt();//введеные вручную значания выдаёт в формате int
            m.setCell(i,j,x);//mat[i][j]=x
        }
    }
    int det = m.calculateRecursiveDeterminant(n);
    label->setText("Determinat: " + QString::number(det));
    label->setAlignment(Qt::AlignCenter);

}



void MainWindow::resizeDeterminantMatrix(QLineEdit* dim, QWidget *matrixFrame){
    int x = dim->text().toInt();//введеные вручную значание выдаёт в формате int
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            delete matrix[i][j];
        }
    }//удаление старой матрицы
    matrix.clear();
    n = x;//заданный размер
    delete grid;
    grid = new QGridLayout();
    grid->setSizeConstraint(QLayout::SetMaximumSize);
    for(int i=0;i<n;i++){
        matrix.append(QVector<QLineEdit*>());
        for(int j=0;j<n;j++){
            matrix[i].append(new QLineEdit);
        }
    }//создает матрицу заданного размера
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]->setFixedSize(30,30);//размерность ячеек матрицы
            matrix[i][j]->setText("0");
            matrix[i][j]->setAlignment(Qt::AlignCenter);//выравнивает текст по центру
            grid->addWidget(matrix[i][j],i,j);//добавляет матрицу в сетку
        }
    }
    matrixFrame->setLayout(grid);
    grid->update();
    matrixFrame->update();
}



MainWindow::~MainWindow(){
    delete ui;
}

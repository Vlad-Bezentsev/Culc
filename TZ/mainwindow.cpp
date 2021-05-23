#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDoubleValidator>
#include<QIntValidator>
#include <QApplication>

bool clear = false, f=true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_data->setValidator(new QIntValidator(1, 1000000000, this));
    ui->lineEdit_sum->setValidator(new QIntValidator(1, 1000000000, this));
    ui->lineEdit_percent->setValidator(new QDoubleValidator(0.1, 99.99, 4, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ravno_released()
{
    QString newLabel;
    double S, p, N, V, X, C;

    //Считаем величину займа из первого lineEdit
    QString S1 = ui->lineEdit_sum->text();
    S = S1.toDouble();

    //Считаем срок кредитования из второго lineEdit
    QString S2 = ui->lineEdit_data->text();
    N = S2.toDouble();

    //Считаем проц. ставку из третьего lineEdit
    QString S3 = ui->lineEdit_percent->text();
    S3.replace(",",".");
    p = S3.toDouble();

    if(p>99.9 || p<=0 || S<=0 || N<=0)
    {
        ui->label_error->setText("Больше 0 и меньше 100%!");
        ui->label_error_2->setText("Больше 0!");
        ui->label_error_3->setText("Больше 0!");
        f=false;
    }else{
        f=true;
    }


    p = p / 100 / 12;

    X = S*(p/(1-pow((1+p),-N)));

    V = X*N;

    C = V-S;

    if(f==true)
    {
    //Выведим результаты
    newLabel=QString::number(V, 'f', 2);
    ui->label_all_sum->setText(newLabel);

    newLabel=QString::number(C, 'f', 2);
    ui->label_plata->setText(newLabel);

    newLabel=QString::number(X, 'f', 2);
    ui->label_month->setText(newLabel);

    ui->label_error->setText("");
    ui->label_error_2->setText("");
    ui->label_error_3->setText("");

    }else{
        ui->label_month->setText("");
        ui->label_plata->setText("");
        ui->label_all_sum->setText("");
    }
}


void MainWindow::on_pushButton_clear_released()
{
        clear = false;
        ui->label_all_sum->setText("");
        ui->label_month->setText("");
        ui->label_error->setText("");
        ui->label_error_2->setText("");
        ui->label_error_3->setText("");
        ui->label_plata->setText("");
        ui->lineEdit_data->setText("");
        ui->lineEdit_percent->setText("");
        ui->lineEdit_sum->setText("");
        f=true;
}



int l=1;
void MainWindow::on_pushButton_light_clicked()
{

    if(l==1)
        {
            ui->centralwidget->setStyleSheet("centralWidget { background-color: grey; }\n"
                          "QWidget:enabled { background-color: #333333; }\n");
            l=l+1;
        }
    else
            {
            ui->centralwidget->setStyleSheet("centralWidget { background-color: grey; }\n"
                              "QWidget:enabled { background-color: #3399FF; }\n");
                l=l-1;
            }
}

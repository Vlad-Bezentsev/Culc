#include "komi.h"
#include "ui_komi.h"
#include <cmath>
#include <QMessageBox>
#include <QValidator>
#include <QVector>
#include <QPair>


int draw=0;
int kol=9, R=200, r=50;
int ox=850;
int oy=300;
double pi=3.1415;

int way[10];

bool visit[45];

int rezult = INT_MAX;

int table[10][10]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};;

QString index, mean, ways;

komi::komi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::komi)
{
    ui->setupUi(this);
    ui->draw->hide();
    ui->result->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();


    for (int i=1;i<=kol;i++){
        for (int j=i+1; j<kol+1; j++){
            index="vvod_" + QString::number(i) + QString::number(j);
            this->findChild<QLineEdit*>(index)->setValidator(new QIntValidator(1, 1000000000));
        }
    }
    QPixmap back("C:/Users/vkadk/Documents/TZ_2/glob.jpg");
    back = back.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, back);
    this->setPalette(palette);
}


komi::~komi()
{
    delete ui;
}

void komi::matrix()
{

    QString mean;
    for (int i=1; i<kol; i++){
        for (int j=i+1; j<kol+1; j++){
            index="vvod_"+ QString::number(i) + QString::number(j);
            mean=this->findChild<QLineEdit*>(index)->text();
            if (mean.length()<1 || mean=='0')
                mean='0';
            this->findChild<QLineEdit*>(index)->setText(mean);
            index="repeat_"+ QString::number(j) + QString::number(i);
            this->findChild<QLabel*>(index)->setText(mean);
        }
    }
}

void komi::paintEvent(QPaintEvent *)
{
    if(draw>1){
    QPainter painter;
    QFont F;
    painter.begin(this);
    QBrush br;
    QPen pen;
    QString num;
    br.setStyle(Qt::SolidPattern);
    br.setColor(Qt::green);
    pen.setWidth(2);

    F.setPointSize(20);
    painter.setPen(pen);
    painter.setBrush(br);
    painter.setFont(F);
    for(int i=1; i<=kol; i++){
        double a;
        a=pi*3/2+pi*2/kol*(i-1);
        int xc;
        xc=ox-r+cos(a)*R;
        int yc;
        yc=oy-r+sin(a)*R;
        painter.drawEllipse(xc,yc,2*r,2*r);


        num.setNum(i);
        painter.drawText(QRect(xc+30,yc+35,40,30),Qt::AlignCenter,num);
    }
    if(draw==2){
        for(int i=1; i<=kol; i++){
        for (int j=i+1; j<=kol; j++){
            if (table[i][j]!=0)
            {
                double a;
                a=pi*3/2+pi*2/kol*i;
                int xc;
                xc=cos(a)*R+ox;
                int yc;
                yc=sin(a)*R+oy;

                double ug2;
                ug2=pi*3/2+pi*2/kol*j;
                double xc2;
                xc2=cos(ug2)*R+ox;
                double yc2;
                yc2=sin(ug2)*R+oy;
                painter.drawLine(xc,yc,xc2,yc2);
                draw=3;
            }

        }
        }
    }
        if(draw==3){
            for(int i=1; i<=kol; i++){
                double a;
                a=pi*3/2+pi*2/kol*(i-1);
                int xc;
                xc=ox-r+cos(a)*R;
                int yc;
                yc=oy-r+sin(a)*R;
                painter.drawEllipse(xc,yc,2*r,2*r);


                num.setNum(i);
                painter.drawText(QRect(xc+30,yc+35,40,30),Qt::AlignCenter,num);
        }
    }
    painter.end();
    }
}

void komi::on_plus_clicked()
{
    ui->result->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->hide();
    ui->label_4->hide();
    ui->draw->hide();
    kol++;
    if (kol<2 || kol>9){
        QMessageBox::warning(this,"Предупреждение","Количество городов должно иметь значение не менее 2 и не более 9 ");
    } else{

        for (int i=1;i<=kol;i++){
            index="st_" + QString::number(i);
            this->findChild<QWidget*>(index)->show();

            index="str_" + QString::number(i);
            this->findChild<QWidget*>(index)->show();

            index="diag_" + QString::number(i);
            this->findChild<QWidget*>(index)->show();
            for (int j=i+1; j<kol+1; j++){
                index="vvod_" + QString::number(i) + QString::number(j);
                this->findChild<QWidget*>(index)->show();

                index="repeat_" + QString::number(j) + QString::number(i);
                this->findChild<QWidget*>(index)->show();
            }
        }
    }
}

void komi::on_minus_clicked()
{
    ui->result->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->hide();
    ui->label_4->hide();
    ui->draw->hide();
    kol--;
    if (kol<2 || kol>9){
        QMessageBox::warning(this,"Предупреждение","Количество городов должно иметь значение не менее 2 и не более 9");
    } else{
        for (int i=kol+1;i<10;i++){
            index="st_" + QString::number(i);
            this->findChild<QWidget*>(index)->hide();

            index="str_" + QString::number(i);
            this->findChild<QWidget*>(index)->hide();

            index="diag_" + QString::number(i);
            this->findChild<QWidget*>(index)->hide();

            for (int j=i-1;j>0;j--){
                index="vvod_" + QString::number(j) + QString::number(i);
                this->findChild<QWidget*>(index)->hide();
            }
            for (int e=1;e<i;e++){
                index="repeat_" + QString::number(i) + QString::number(e);
                this->findChild<QWidget*>(index)->hide();
            }
        }
    }
}

void komi::on_draw_clicked()
{
    matrix();
    for (int i=1;i<=kol;i++){
    for (int j=i+1; j<=kol; j++){
        index="vvod_"+ QString::number(i) + QString::number(j);
        int x=this->findChild<QLineEdit*>(index)->text().toInt();
        table[i][j]=x;
        table[j][i]=table[i][j];
    }
    }
    draw=2;
    this->repaint();
    ui->result->show();
    ui->label->hide();
    ui->label_2->hide();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->hide();
    ui->label_4->hide();
}

void SaveWays(int arg[])
{
    for (int i = 0; i < kol; i++)
        way[i] = arg[i];
    way[kol] = arg[0];
}


int FindfirstMin(int adj[10][10], int i)
{
   int min = INT_MAX;
   for (int k = 0; k < kol; k++)
       if (adj[i][k] < min && i != k)
           min = adj[i][k];
   return min;
}


int FindsecondMin(int adj[10][10], int i)
{
   int fst = INT_MAX, sec = INT_MAX;
   for (int j = 0; j < kol; j++)
   {
       if (i == j)
           continue;

       if (adj[i][j] <= fst)
       {
           sec = fst;
           fst = adj[i][j];
       }
       else if (adj[i][j] <= sec && adj[i][j] != fst)
           sec = adj[i][j];
   }
   return sec;
}

void Rec(int adj[10][10], int b, int weight,int l, int arg[])
{

    {

        if (l == kol)
        {

            if (adj[arg[l - 1]][arg[0]] != 0)
            {

                int curr_res =weight + adj[arg[l - 1]][arg[0]];


                if (curr_res < rezult)
                {
                    SaveWays(arg);
                    rezult = curr_res;
                }
            }
            return;
        }

        for (int i = 0; i < kol; i++)
        {

            if (adj[arg[l - 1]][i] != 0 &&
     visit[i] == false)
            {
                int temp = b;
     weight += adj[arg[l - 1]][i];


                if (l == 1)
     b -= ((FindfirstMin(adj, arg[l - 1]) + FindfirstMin(adj, i)) / 2);
                else
     b -= ((FindsecondMin(adj, arg[l - 1]) + FindfirstMin(adj, i)) / 2);


                if (b + weight < rezult)
                {
     arg[l] = i;
     visit[i] = true;


                  Rec(adj, b, weight, l + 1,arg);
                }


     weight -= adj[arg[l - 1]][i];
     b = temp;


                memset(visit, false, sizeof(visit));
                for (int j = 0; j <= l - 1; j++)
     visit[arg[j]] = true;
            }
        }
    }
}

void Voyager(int adj[10][10])
{
    int path[11];

    int k = 0;
    memset(path, -1, sizeof(path));
    memset(visit, 0, sizeof(path));

    for (int i = 0; i < kol; i++)
 k += (FindfirstMin(adj, i) + FindsecondMin(adj, i));


 k = (k & 1) ? k / 2 + 1 : k / 2;

 visit[0] = true;
 path[0] = 0;


    Rec(adj, k, 0, 1, path);
}

void komi::on_result_clicked()
{
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    for (int i=1; i<kol; i++){
    for (int j=i; j<=kol; j++){
        if(i!=j){
        index="vvod_"+ QString::number(i) + QString::number(j);
        int x=this->findChild<QLineEdit*>(index)->text().toInt();
        table[i-1][j-1]=x;
        table[j-1][i-1]=table[i-1][j-1];}
    }
    }
    Voyager(table);

    for (int i = 0; i < kol; i++)
                {
     way[i]=way[i] + 1;
                }
    if(rezult==INT_MAX){
    QMessageBox::warning(this,"Предупреждение","Таблица не заполнена");
    ui->draw->hide();
    ui->result->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->hide();
    ui->label_4->hide();
    }
     ui->label->setText(QString::number(rezult));

     for(int i=0;i<kol;i++){
         ways=ways + QString::number(way[i]) + "->";

     }
     ways=ways+QString::number(way[0]);
     ui->label_2->setText(ways);
     ways="";

     memset(visit,0,sizeof visit);
                memset(way,0,sizeof way);
      rezult=INT_MAX;
}

void komi::on_matrix_clicked()
{
    matrix();
    ui->draw->show();
    draw=1;
    this->repaint();
    ui->result->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->hide();
    ui->label_4->hide();
}

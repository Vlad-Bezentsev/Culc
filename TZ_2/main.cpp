#include "komi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    komi w;
    w.show();
    return a.exec();
}

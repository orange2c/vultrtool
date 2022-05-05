

#include "pagelogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PageLogin w;
    w.show();

    return a.exec();

}

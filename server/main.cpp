
#include "server.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    return a.exec();
}

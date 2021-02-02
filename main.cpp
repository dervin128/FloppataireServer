#include <QCoreApplication>
#include "FloppaServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FloppaServer* server = new FloppaServer();
    return a.exec();
}

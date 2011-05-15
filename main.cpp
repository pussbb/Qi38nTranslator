#include <QtGui/QApplication>
#include "headers/qi38ntranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("Qi38nTr");
    QApplication::setApplicationName("Qi38nTr");
    QApplication::setApplicationVersion("0.0.0.5");
    Qi38nTranslator w;
    w.show();

    return a.exec();
}

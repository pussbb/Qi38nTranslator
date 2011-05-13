#include <QtGui/QApplication>
#include "headers/qi38ntranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qi38nTranslator w;
    w.show();

    return a.exec();
}

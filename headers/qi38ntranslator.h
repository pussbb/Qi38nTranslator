#ifndef QI38NTRANSLATOR_H
#define QI38NTRANSLATOR_H

#include "headers/qcorewindow.h"

namespace Ui {
    class Qi38nTranslator;
}

class Qi38nTranslator : public QCoreWindow
{
    Q_OBJECT

public:
    explicit Qi38nTranslator(QWidget *parent = 0);
    ~Qi38nTranslator();

private slots:
    void on_actionAbout_Qt_triggered();

private:
    Ui::Qi38nTranslator *ui;
};

#endif // QI38NTRANSLATOR_H

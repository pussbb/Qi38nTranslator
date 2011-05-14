#include "headers/qi38ntranslator.h"
#include "ui_qi38ntranslator.h"

Qi38nTranslator::Qi38nTranslator(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::Qi38nTranslator)
{
    ui->setupUi(this);
    buildLangMenu("qi38ntr");
    langMenuToMenuBar("menuOptions");
}

Qi38nTranslator::~Qi38nTranslator()
{
    delete ui;
}

void Qi38nTranslator::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt ();
}

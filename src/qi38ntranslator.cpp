#include "headers/qi38ntranslator.h"
#include "ui_qi38ntranslator.h"

Qi38nTranslator::Qi38nTranslator(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::Qi38nTranslator)
{
    ui->setupUi(this);
}

Qi38nTranslator::~Qi38nTranslator()
{
    delete ui;
}

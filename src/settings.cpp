#include "headers/settings.h"
#include "ui_settings.h"
#include <QDebug>
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QRegExp nameExpr("[a-zA-Z]+");
    ui->phpTemplName->setValidator(new QRegExpValidator(nameExpr ,this));
    templateDir = QDir(QApplication::applicationDirPath()+QDir::toNativeSeparators("/templates/"));
    updatePhpTemplatesList ();
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_buttonBox_accepted()
{
    accept ();
}

void Settings::updatePhpTemplatesList ()
{
    ui->phpTemplatesList->clear ();
    QStringList fileNames =
            templateDir.entryList(QStringList("*.phptpl"));
    fileNames.replaceInStrings (".phptpl","");
    ui->phpTemplatesList->insertItems (0,fileNames);
    int current = ui->phpTemplatesList->findText (ui->phpTemplName->text ());
    if ( current != -1)
        ui->phpTemplatesList->setCurrentIndex ( current );

}

void Settings::on_phpTemplSave_clicked()
{
    if(!templateDir.exists ())
        return ;
    QString file = templateDir.canonicalPath()+QDir::toNativeSeparators("/")
            +ui->phpTemplName->text () + ".phptpl";
    QSettings tplSettings(file,QSettings::IniFormat);
    tplSettings.setValue ("name",ui->phpTemplName->text());
    tplSettings.setValue ("mimetypes","php");
    tplSettings.setValue ("searchfor",ui->searchFor->text ());
    tplSettings.setValue ("ignore",ui->ignoreStr->toPlainText ().split ("\n"));
    tplSettings.sync ();
    updatePhpTemplatesList();
}

void Settings::on_phpTemplatesList_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if(!templateDir.exists ())
        return ;
    QString file = templateDir.canonicalPath()+QDir::toNativeSeparators("/")
            +ui->phpTemplatesList->currentText ()+ ".phptpl";
    QSettings tplSettings(file,QSettings::IniFormat);
    ui->phpTemplName->setText (tplSettings.value ("name","").toString ());
    ui->searchFor->setText (tplSettings.value ("searchfor","").toString ());
    ui->ignoreStr->setText (tplSettings.value ("ignore","").toStringList ().join ("\n"));
}

void Settings::on_newPhpTemplate_clicked()
{
    ui->phpTemplName->setText ("");
    ui->searchFor->setText ("");
    QStringList ignore;
    ignore << "<script.*script>"
           << "<!--.*-->"
           << "//.*\n"
           << "/\*.*/";
    ui->ignoreStr->setText (ignore.join ("\n"));
}

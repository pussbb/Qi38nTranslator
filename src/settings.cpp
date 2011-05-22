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
    googleTranslator = new QGoogleTranslator(this,ui->gLangFrom,ui->gLangTo);
    if(settings.value ("GoogleTransl/glangfrom","").toString ()!=""
            && settings.value ("GoogleTransl/glangto","").toString () != "")
        googleTranslator->setDefaultLangs (settings.value ("GoogleTransl/glangfrom","").toString (),
                                       settings.value ("GoogleTransl/glangto","").toString ());
    else
        googleTranslator->setDefaultLangs ();
    ui->templatesList->addItem (QIcon(":/mimetypes/php"),"PHP","php");
    ui->templatesList->addItem (QIcon(":/mimetypes/js"),"JavaScript","js");
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_buttonBox_accepted()
{
    settings.setValue ("Core/save_locale",ui->saveLocale->isChecked ());
    settings.setValue ("GoogleTransl/glangfrom",ui->gLangFrom->itemData (
                           ui->gLangFrom->currentIndex ()));
    settings.setValue ("GoogleTransl/glangto",ui->gLangTo->itemData (
                           ui->gLangTo->currentIndex ()));
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

void Settings::updateJsTemplatesList ()
{
    ui->phpTemplatesList->clear ();
    QStringList fileNames =
            templateDir.entryList(QStringList("*.jstpl"));
    fileNames.replaceInStrings (".jstpl","");
    ui->phpTemplatesList->insertItems (0,fileNames);
    int current = ui->phpTemplatesList->findText (ui->phpTemplName->text ());
    if ( current != -1)
        ui->phpTemplatesList->setCurrentIndex ( current );
}

void Settings::on_phpTemplSave_clicked()
{
    if(!templateDir.exists ())
        return ;
    QString prefix = ui->templatesList->itemData (ui->templatesList->currentIndex ())
                    .toString ();
    QString file = templateDir.canonicalPath()+QDir::toNativeSeparators("/")
            +ui->phpTemplName->text ()
            + QString(".%1tpl").arg (prefix);
    QSettings tplSettings(file,QSettings::IniFormat);
    tplSettings.setValue ("name",ui->phpTemplName->text());
    tplSettings.setValue ("mimetypes",prefix);
    tplSettings.setValue ("filext",ui->fileExt->text ());
    tplSettings.setValue ("searchfor",ui->searchFor->text ());
    tplSettings.setValue ("ignore",ui->ignoreStr->toPlainText ().split ("\n"));
    tplSettings.setValue ("langfilerx",ui->langFileRx->text ());
    tplSettings.setValue ("savetemplate",ui->saveTemplate->toPlainText ());
    tplSettings.sync ();
    updatePhpTemplatesList();
}

void Settings::on_phpTemplatesList_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if(!templateDir.exists ())
        return ;
    QString prefix = ui->templatesList->itemData (ui->templatesList->currentIndex ())
                    .toString ();
    QString file = templateDir.canonicalPath()+QDir::toNativeSeparators("/")
            +ui->phpTemplatesList->currentText ()
            + QString(".%1tpl").arg (prefix);
    QSettings tplSettings(file,QSettings::IniFormat);
    ui->phpTemplName->setText (tplSettings.value ("name","").toString ());
    ui->searchFor->setText (tplSettings.value ("searchfor","").toString ());
    ui->ignoreStr->setText (tplSettings.value ("ignore","").toStringList ().join ("\n"));
    ui->langFileRx->setText (tplSettings.value ("langfilerx","").toString ());
    ui->saveTemplate->setText (tplSettings.value ("savetemplate","").toString ());
    ui->fileExt->setText (tplSettings.value ("filext",prefix).toString ());
}

void Settings::on_newPhpTemplate_clicked()
{
    ui->phpTemplName->setText ("");
    ui->searchFor->setText ("");
    ui->ignoreStr->setText ("");
}

void Settings::on_buttonBox_rejected()
{
    reject ();
}



void Settings::on_listWidget_itemClicked(QListWidgetItem* item)
{
    Q_UNUSED(item);
    int index = ui->listWidget->currentIndex ().row ();
    ui->settingsWidget->setCurrentIndex (index);
}

void Settings::on_templatesList_currentIndexChanged(int index)
{
    QString prefix = ui->templatesList->itemData (index).toString ();
    if( prefix =="php")
        updatePhpTemplatesList ();
    if (prefix == "js")
        updateJsTemplatesList ();
}

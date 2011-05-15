#include "headers/qi38ntranslator.h"
#include "ui_qi38ntranslator.h"
#include <QFileDialog>
Qi38nTranslator::Qi38nTranslator(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::Qi38nTranslator)
{
    ui->setupUi(this);
    buildLangMenu("qi38ntr");
    langMenuToMenuBar("menuOptions");
    templateDir = QDir(QApplication::applicationDirPath()+QDir::toNativeSeparators("/templates/"));
    updateProjectTemplates();
}

Qi38nTranslator::~Qi38nTranslator()
{
    delete ui;
}

void Qi38nTranslator::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt ();
}

void Qi38nTranslator::on_actionClose_triggered()
{
   exit (0);
}

void Qi38nTranslator::on_selectDestFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "",
                                                tr("Files (*)"));
    if( !file.isEmpty() )
        ui->destFile->setText (file);
}

void Qi38nTranslator::on_selectSourceFolder_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                        "",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
        ui->sourceFolder->setText(dir);
}

#include <headers/settings.h>
void Qi38nTranslator::on_actionSettings_triggered()
{
    Settings *settingsUI = new Settings(this);
    settingsUI->show();
}

void Qi38nTranslator::updateProjectTemplates ()
{
    QStringList fileNames =
            templateDir.entryList(QStringList("*"),QDir::Files);
    fileNames.replaceInStrings (".*tpl","");
    QRegExp rx("\\.(.*)tpl");//"\\.(.*)tpl"
    QString icon = "php";
    foreach (QString file, fileNames) {

        rx.indexIn(file, 0);
        if(rx.cap (1) == "php")
            icon = ":/mimetypes/php";
        file.replace (rx.cap (0),"");
        qDebug ()<<rx.cap (1);
        qDebug ()<<rx.cap (0);
        ui->projectTemplates->insertItem (0,QIcon(icon),file,rx.cap (1));
    }
}

void Qi38nTranslator::on_projectTemplates_currentIndexChanged(int index)
{
  Q_UNUSED(index);

  QString file = templateDir.canonicalPath()+QDir::toNativeSeparators("/")
            + ui->projectTemplates->currentText ()+ "."
            + ui->projectTemplates->itemData (0,Qt::UserRole).toString ()
            + "tpl";
  QSettings tplSettings(file,QSettings::IniFormat);

  ui->searchFor->setText (tplSettings.value ("searchfor","").toString ());
  ui->fileExt->setText (tplSettings.value ("mimetypes","").toString ());
  ui->ignoreStr->setText (tplSettings.value ("ignore","").toStringList ().join ("\n"));
}

void Qi38nTranslator::on_createProject_clicked()
{
    settings.setValue ("Projects/"+ui->projetName->text(),ui->projetName->text());
    QString section = ui->projetName->text();
    settings.beginGroup (section);
    settings.setValue ("destfile",ui->destFile->text ());
    settings.setValue ("sourcedir",ui->sourceFolder->text ());
    settings.setValue ("template",ui->projectTemplates->currentText ());
    settings.endGroup ();
}

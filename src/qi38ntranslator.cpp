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
    QRegExp sep("\\.*tpl");//"\\.(.*)tpl"
    foreach (QString file, fileNames) {
        QString t = file.section (sep,0,2);
        qDebug ()<<t;
       // ui->projectTemplates->insertItem (0,);
    }
   ui->projectTemplates->insertItems (0,fileNames);


}

void Qi38nTranslator::on_projectTemplates_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

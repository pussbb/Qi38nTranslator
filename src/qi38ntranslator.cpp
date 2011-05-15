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
    updateProjectList();
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
    settings.setValue ("Projects/"+ui->projetName->text(),ui->projectTemplates->itemData (0,Qt::UserRole));
    QString section = ui->projetName->text();
    settings.beginGroup (section);
    settings.setValue ("destfile",ui->destFile->text ());
    settings.setValue ("sourcedir",ui->sourceFolder->text ());
    settings.setValue ("template",ui->projectTemplates->currentText ());
    settings.endGroup ();
    updateProjectList();
}

void Qi38nTranslator::updateProjectList ()
{
    ui->projectList->clear ();
    settings.beginGroup ("Projects");
    QStringList keys  = settings.allKeys ();

    foreach (QString key, keys)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->projectList);
        item->setText (key);
        item->setIcon (QIcon(":/mimetypes/"+settings.value (key,"php").toString ()));
    }
    settings.endGroup ();
}

void Qi38nTranslator::on_projectList_itemDoubleClicked(QListWidgetItem* item)
{
    settings.beginGroup (item->text());
    ui->projetName->setText (item->text ());
    ui->destFile->setText(settings.value ("destfile","").toString ());
    ui->sourceFolder->setText (settings.value ("sourcedir","").toString ());
    int itemIndex= ui->projectTemplates->findText (settings.value ("template","").toString ());
    ui->projectTemplates->setCurrentIndex (itemIndex);
    settings.endGroup ();
}

void Qi38nTranslator::on_openProject_clicked()
{
///
}

void Qi38nTranslator::on_projectList_customContextMenuRequested(QPoint pos)
{
    if(ui->projectList->currentIndex().isValid()
            && ui->projectList->currentItem()->isSelected())
    {
        QMenu *m=new QMenu();
        pos.setX(pos.x()-5);
        pos.setY(pos.y()+5);
        m->addAction(ui->actionRemove_Project);
        m->exec(ui->projectList->mapToGlobal(pos));
    }
}

void Qi38nTranslator::on_actionRemove_Project_triggered()
{
    QListWidgetItem *item = ui->projectList->currentItem ();
    settings.remove ("Projects/"+item->text());
    settings.remove (item->text());
    updateProjectList ();
    settings.sync ();
}

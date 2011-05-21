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
    googleTranslator = new QGoogleTranslator(this,ui->gLangFrom,ui->gLangTo);
    connect (googleTranslator, SIGNAL(translationFinished(QString))
             ,this, SLOT(updateGoogleTranslation(QString)));
    googleTranslator->setDefaultLangs ();

}

void Qi38nTranslator::updateGoogleTranslation (QString translation)
{
    ui->gTranslated->setText (translation);
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

void Qi38nTranslator::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        ui->retranslateUi(this);
        break;
    }
    default:
        break;
    }
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
    ui->langFileRx->setText (tplSettings.value ("langfilerx","").toString ());
    ui->saveTemplate->setText (tplSettings.value ("savetemplate","").toString ());
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

    foreach (QString key, keys) {
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
    progress = new QProgressDialog("Operation in progress.", "Cancel",0,0,this);

    ui->tranlationList->clear ();
    ui->fileTree->clear ();
    ui->translation->clear ();
    ui->currentText->clear ();

    ui->stackedWidget->setCurrentIndex(1);
    ui->actionSave->setEnabled (true);
    ui->actionBackToMainPage->setEnabled (true);
    parseTranslationFile (ui->destFile->text ());
    findInFolder (ui->sourceFolder->text ());
    progress->hide ();
}

void Qi38nTranslator::on_projectList_customContextMenuRequested(QPoint pos)
{
    if(ui->projectList->currentIndex().isValid()
            && ui->projectList->currentItem()->isSelected()) {
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

void Qi38nTranslator::on_actionBackToMainPage_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Qi38nTranslator::parseTranslationFile (QString fileName)
{
    QFile file(fileName);

    if (!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Could't open file for the reading"));
        return;
    }
    QTextStream stream ( &file );
    stream.setCodec("UTF-8");
    QString strTmp;
    strTmp =  stream.readAll();
    QRegExp rx( ui->langFileRx->text ());
    rx.setMinimal(true);
    QString strTranslated;
    int pos = 0;

    while((pos = rx.indexIn(strTmp, pos)) != -1) {
        QListWidgetItem *item = new QListWidgetItem(rx.cap(1),ui->tranlationList);
        strTranslated = rx.cap(2);
        item->setData(Qt::UserRole,rx.cap(2));

        if(!strTranslated.isEmpty ())
            item->setIcon (QIcon(":/main/main/accept.png"));
        else
            item->setIcon (QIcon(":/main/main/warning.png"));
        item->setBackgroundColor (QColor(Qt::red));
        pos += rx.matchedLength();

    }
}

void Qi38nTranslator::findInFolder (QString folderName)
{
    QString strTmp;
    QStringList list;
    QDirIterator directory_walker(folderName, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(directory_walker.hasNext()) {
        directory_walker.next();
        if(directory_walker.fileInfo().completeSuffix() == ui->fileExt->text ()) {
            QTreeWidgetItem *item=new QTreeWidgetItem();
            item->setText(0,directory_walker.fileName());
            item->setData(0,Qt::UserRole,directory_walker.filePath());
            item->setToolTip(0,directory_walker.filePath());
            QFile file(directory_walker.filePath());
            if (file.open(QIODevice::ReadOnly)) {
                QTextStream stream ( &file );
                stream.setCodec("UTF-8");
                list.clear ();
                strTmp =  stream.readAll();
                foreach (QString ignore, ui->ignoreStr->toPlainText ().split ("\n")) {
                    strTmp = strTmp.replace(ignore,"");
                }
                QRegExp rx(ui->searchFor->text ());
                rx.setMinimal(true);
                int pos = 0;
                while((pos = rx.indexIn(strTmp, pos)) != -1) {
                    QTreeWidgetItem *childitem=new QTreeWidgetItem(item);
                    childitem->setText(0,rx.cap(1));
                    list << rx.cap(1);
                    pos += rx.matchedLength();
                }
                list.removeDuplicates();
                if(ui->tranlationList->count() > 0 )
                {
                    foreach (QString msg, list) {
                        QList<QListWidgetItem *>   itemList =
                                ui->tranlationList->findItems(msg,Qt::MatchExactly);
                        if(itemList.count() == 0){
                            QListWidgetItem *itemTr = new QListWidgetItem(ui->tranlationList);
                            itemTr->setText (msg);
                            itemTr->setIcon (QIcon(":/main/main/warning.png"));
                            itemTr->setBackgroundColor (QColor(Qt::red));
                        }
                        else {
                            foreach (QListWidgetItem *itemTr, itemList) {
                                itemTr->setBackgroundColor (QColor(Qt::green));
                            }
                        }
                    }
                }
                else{
                    foreach (QString msg, list) {
                        QListWidgetItem *itemTr = new QListWidgetItem(ui->tranlationList);
                        itemTr->setText (msg);
                        itemTr->setIcon (QIcon(":/main/main/warning.png"));
                        itemTr->setBackgroundColor (QColor(Qt::red));
                    }
                }
            }
            if(item->childCount() > 0)
                                ui->fileTree->addTopLevelItem(item);
        }
    }
}

void Qi38nTranslator::on_tranlationList_itemDoubleClicked(QListWidgetItem* item)
{
    ui->currentText->setText (item->text ());
    ui->translation->setText (item->data (Qt::UserRole).toString ());
    if(ui->googleTranslator->isChecked ())
        googleTranslator->translateString (item->text ());
    currentTranslationItem = item;
}

void Qi38nTranslator::on_findInFile_clicked()
{
    if(ui->tranlationList->currentIndex().isValid()
            && ui->tranlationList->currentItem()->isSelected()) {
        foreach (QTreeWidgetItem *listItem,fileTreeList) {
            listItem->parent()->setExpanded(false);
            listItem->setBackgroundColor(0,QColor(Qt::transparent));
        }
        fileTreeList.clear();
        fileTreeList = ui->fileTree->findItems(ui->tranlationList->currentItem ()->text ()
                                                  ,Qt::MatchContains |Qt::MatchRecursive, 0);
        foreach (QTreeWidgetItem *listItem,fileTreeList) {
            listItem->parent()->setExpanded(true);
            listItem->setBackgroundColor(0,QColor(Qt::red));
        }
    }
}

void Qi38nTranslator::on_acceptTranslation_clicked()
{
    currentTranslationItem->setData (Qt::UserRole,ui->translation->toPlainText ());
    if (ui->translation->toPlainText ().isEmpty ()) {
        currentTranslationItem->setIcon (QIcon(":/main/main/warning.png"));
        currentTranslationItem->setBackgroundColor (QColor(Qt::red));
    }
    else {
        currentTranslationItem->setIcon (QIcon(":/main/main/accept.png"));
        currentTranslationItem->setBackgroundColor (QColor(Qt::green));
    }
}

void Qi38nTranslator::on_clearTranslation_clicked()
{
    ui->translation->clear ();
}

void Qi38nTranslator::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                    tr("QFileDialog::getSaveFileName()"),
                                    ui->destFile->text (),
                                    tr("All Files (*);;Text Files (*.txt)")
                                    );
    if (fileName.isEmpty ())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning (this, tr("Saving error"),
                             tr("Cannot write file %1.")
                             .arg(fileName));
        return;
    }

    QRegExp rx("\\{(.*)\\}");
    rx.indexIn(ui->saveTemplate->toPlainText (), 0);
    qDebug ()<<rx.cap (1);
    QStringList data;
    QString tmp;
    for (int i = 0; i < ui->tranlationList->count (); i++) {
        tmp = rx.cap (1);
        tmp.replace ("{key}",ui->tranlationList->item (i)->text ());
        tmp.replace ("{value}",ui->tranlationList->item (i)->data (Qt::UserRole).toString ());
        data << tmp;
    }
    QString toSave = ui->saveTemplate->toPlainText ();
    toSave.replace (rx.cap (),data.join ("\n"));

    file.write(toSave.toUtf8());
    file.close ();
}

void Qi38nTranslator::on_gTransUpdate_clicked()
{
    if(!ui->currentText->text ().isEmpty ())
         googleTranslator->translateString (ui->currentText->text ());

}

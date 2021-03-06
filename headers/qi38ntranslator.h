#ifndef QI38NTRANSLATOR_H
#define QI38NTRANSLATOR_H

#include "headers/qcorewindow.h"
#include <QDir>
#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QDirIterator>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QProgressDialog>
#include "headers/qgoogletranslator.h"
namespace Ui {
    class Qi38nTranslator;
}

class Qi38nTranslator : public QCoreWindow
{
    Q_OBJECT

public:
    explicit Qi38nTranslator(QWidget *parent = 0);
    ~Qi38nTranslator();
    QDir templateDir;
    QList<QTreeWidgetItem *> fileTreeList;
    QListWidgetItem* currentTranslationItem;
    QProgressDialog *progress;
    QGoogleTranslator *googleTranslator;

public slots:
    void updateGoogleTranslation(QString translation);
private slots:
    void on_actionAbout_Qt_triggered();

    void on_actionClose_triggered();

    void on_selectDestFile_clicked();

    void on_selectSourceFolder_clicked();

    void on_actionSettings_triggered();
    void updateProjectTemplates();
    void updateProjectList();
    void changeEvent(QEvent *e);
    void on_projectTemplates_currentIndexChanged(int index);

    void on_createProject_clicked();

    void on_projectList_itemDoubleClicked(QListWidgetItem* item);

    void on_openProject_clicked();

    void on_projectList_customContextMenuRequested(QPoint pos);

    void on_actionRemove_Project_triggered();

    void on_actionBackToMainPage_triggered();
    void parseTranslationFile(QString fileName);
    void findInFolder(QString folderName);

    void on_tranlationList_itemDoubleClicked(QListWidgetItem* item);

    void on_findInFile_clicked();

    void on_acceptTranslation_clicked();

    void on_clearTranslation_clicked();

    void on_actionSave_triggered();

    void on_gTransUpdate_clicked();

    void on_fileTree_customContextMenuRequested(QPoint pos);

    void on_actionOpen_File_triggered();

    void on_clearProjValues_clicked();

    void on_actionBack_to_Translation_triggered();

    void on_actionRemove_Translation_triggered();

    void on_tranlationList_customContextMenuRequested(QPoint pos);

private:
    Ui::Qi38nTranslator *ui;
};

#endif // QI38NTRANSLATOR_H

#ifndef QI38NTRANSLATOR_H
#define QI38NTRANSLATOR_H

#include "headers/qcorewindow.h"
#include <QDir>
#include <QListWidgetItem>
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

private slots:
    void on_actionAbout_Qt_triggered();

    void on_actionClose_triggered();

    void on_selectDestFile_clicked();

    void on_selectSourceFolder_clicked();

    void on_actionSettings_triggered();
    void updateProjectTemplates();
    void updateProjectList();

    void on_projectTemplates_currentIndexChanged(int index);

    void on_createProject_clicked();

    void on_projectList_itemDoubleClicked(QListWidgetItem* item);

    void on_openProject_clicked();

    void on_projectList_customContextMenuRequested(QPoint pos);

    void on_actionRemove_Project_triggered();

private:
    Ui::Qi38nTranslator *ui;
};

#endif // QI38NTRANSLATOR_H

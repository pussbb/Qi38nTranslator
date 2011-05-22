#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QDir>
#include <QSettings>
#include <QListWidgetItem>
#include "headers/qgoogletranslator.h"
namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QDir templateDir;
    QSettings settings;
private slots:
    void on_buttonBox_accepted();
    void updatePhpTemplatesList();
    void on_phpTemplSave_clicked();
    void updateJsTemplatesList();
    void on_phpTemplatesList_currentIndexChanged(int index);

    void on_newPhpTemplate_clicked();

    void on_buttonBox_rejected();


    void on_listWidget_itemClicked(QListWidgetItem* item);

    void on_templatesList_currentIndexChanged(int index);

private:
    Ui::Settings *ui;
    QGoogleTranslator *googleTranslator;
};

#endif // SETTINGS_H

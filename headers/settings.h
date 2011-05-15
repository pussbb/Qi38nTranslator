#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QDir>
#include <QSettings>

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

private slots:
    void on_buttonBox_accepted();
    void updatePhpTemplatesList();
    void on_phpTemplSave_clicked();

    void on_phpTemplatesList_currentIndexChanged(int index);

    void on_newPhpTemplate_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H

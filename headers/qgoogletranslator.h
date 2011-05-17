#ifndef QGOOGLETRANSLATOR_H
#define QGOOGLETRANSLATOR_H
#include <QComboBox>
class QGoogleTranslator : public QObject
{
    Q_OBJECT
public:
    explicit QGoogleTranslator(QObject *parent = 0,QComboBox *from = new QComboBox()
                               , QComboBox *to = new QComboBox());
    QString version();
    QComboBox *from;
    QComboBox *to;
    void setDefaultLangs(QString langFrom = "en", QString langTo = "ru");
private:
    void buildListFrom();
    void buildListTo();

};

#endif // QGOOGLETRANSLATOR_H

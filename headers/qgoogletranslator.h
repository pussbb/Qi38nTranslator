#ifndef QGOOGLETRANSLATOR_H
#define QGOOGLETRANSLATOR_H
#include <QComboBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "qt-json/json.h"
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
    void translateString(QString text);
signals:
    void translationFinished(QString translation);
public slots:
     void finishedSlot(QNetworkReply*);
private:
    QNetworkAccessManager *nam;
    void buildListFrom();
    void buildListTo();

};

#endif // QGOOGLETRANSLATOR_H

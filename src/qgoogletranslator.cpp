#include "headers/qgoogletranslator.h"
#include <QDebug>
QGoogleTranslator::QGoogleTranslator(QObject *parent, QComboBox *from, QComboBox *to) :
    QObject(parent),from(from), to(to)
{
    buildListFrom ();
    buildListTo ();
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));
}

QString QGoogleTranslator::version ()
{
    return "hi";
}
void QGoogleTranslator::finishedSlot(QNetworkReply* reply)
{
    // Reathising attributes of the reply
    // e.g. the HTTP    QTextStream stream ( &file );

    QVariant statusCodV =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a rethisirect:
    QVariant redirectionTargetUrl =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    QTextStream stream ( reply );
    stream.setCodec("UTF-8");
    QString strTmp;
    strTmp =  stream.readAll();
    QVariant response = Json::parse(strTmp);
    emit translationFinished(response.toMap ().value ("responseData")
                             .toMap ().value ("translatedText").toString ());
}

void QGoogleTranslator::translateString (QString text)
{
    QUrl url("https://ajax.googleapis.com/ajax/services/language/translate");
    QString lang = from->itemData (from->currentIndex (),Qt::UserRole).toString ()
            +"|"
            +to->itemData (to->currentIndex ()).toString ();
    QList<QPair<QString, QString> > query;
    query.append (qMakePair(QString("v"), QString("1.0")));
    query.append (qMakePair(QString("langpair"),QString(lang.toUtf8 ())));
    query.append (qMakePair(QString("q"),QString(text.toUtf8 ())));
    url.setQueryItems (query);
qDebug()<<url.toString ();
    nam->get(QNetworkRequest(url));
}

void QGoogleTranslator::buildListFrom ()
{
    from->addItem(QIcon(":flags/al.png"),tr("Albanian"),"sq");
    from->addItem(QIcon(":flags/ar.png"),tr("Arabic"),"ar");
    from->addItem(QIcon(":flags/eu.png"),tr("Basque"),"eu");
    from->addItem(QIcon(":flags/be.png"),tr("Belarusian"),"be");
    from->addItem(QIcon(":flags/bg.png"),tr("Bulgarian"),"bg");
    from->addItem(QIcon(":flags/ca.png"),tr("Catalan"),"ca");
    from->addItem(QIcon(":flags/cn.png"),tr("Chinese Simplified"),"zh-CN");
    from->addItem(QIcon(":flags/tw.png"),tr("Chinese Traditional"),"zh-TW");
    from->addItem(QIcon(":flags/hr.png"),tr("Croatian"),"hr");
    from->addItem(QIcon(":flags/cz.png"),tr("Czech"),"cs");
    from->addItem(QIcon(":flags/dk.png"),tr("Danish"),"da");
    from->addItem(QIcon(":flags/nl.png"),tr("Dutch"),"nl");
    from->addItem(QIcon(":flags/gb.png"),tr("English"),"en");
    from->addItem(QIcon(":flags/et.png"),tr("Estonian"),"et");
    from->addItem(QIcon(":flags/tl.png"),tr("Filipino"),"tl");
    from->addItem(QIcon(":flags/fi.png"),tr("Finnish"),"fi");
    from->addItem(QIcon(":flags/fr.png"),tr("French"),"fr");
    from->addItem(QIcon(":flags/gl.png"),tr("Galician"),"gl");
    from->addItem(QIcon(":flags/de.png"),tr("German"),"de");
    from->addItem(QIcon(":flags/gr.png"),tr("Greek"),"el");
    from->addItem(QIcon(":flags/ht.png"),tr("Haitian Creole"),"ht");
    from->addItem(QIcon(":flags/il.png"),tr("Hebrew"),"iw");
    from->addItem(QIcon(":flags/in.png"),tr("Hindi"),"hi");
    from->addItem(QIcon(":flags/hu.png"),tr("Hungarian"),"hu");
    from->addItem(QIcon(":flags/is.png"),tr("Icelandic"),"is");
    from->addItem(QIcon(":flags/id.png"),tr("Indonesian"),"id");
    from->addItem(QIcon(":flags/ga.png"),tr("Irish"),"ga");
    from->addItem(QIcon(":flags/it.png"),tr("Italian"),"it");
    from->addItem(QIcon(":flags/jp.png"),tr("Japanese"),"ja");
    from->addItem(QIcon(":flags/lv.png"),tr("Latvian"),"lv");
    from->addItem(QIcon(":flags/lt.png"),tr("Lithuanian"),"lt");
    from->addItem(QIcon(":flags/mk.png"),tr("Macedonian"),"mk");
    from->addItem(QIcon(":flags/ms.png"),tr("Malay"),"ms");
    from->addItem(QIcon(":flags/mt.png"),tr("Maltese"),"mt");
    from->addItem(QIcon(":flags/no.png"),tr("Norwegian"),"no");
    from->addItem(QIcon(":flags/ir.png"),tr("Persian"),"fa");
    from->addItem(QIcon(":flags/pl.png"),tr("Polish"),"pl");
    from->addItem(QIcon(":flags/pt.png"),tr("Portuguese"),"pt");
    from->addItem(QIcon(":flags/ro.png"),tr("Romanian"),"ro");
    from->addItem(QIcon(":flags/ru.png"),tr("Russian"),"ru");
    from->addItem(QIcon(":flags/sr.png"),tr("Serbian"),"sr");
    from->addItem(QIcon(":flags/sk.png"),tr("Slovak"),"sk");
    from->addItem(QIcon(":flags/sl.png"),tr("Slovenian"),"sl");
    from->addItem(QIcon(":flags/es.png"),tr("Spanish"),"es");
    from->addItem(QIcon(":flags/tz.png"),tr("Swahili"),"sw");
    from->addItem(QIcon(":flags/sv.png"),tr("Swedish"),"sv");
    from->addItem(QIcon(":flags/th.png"),tr("Thai"),"th");
    from->addItem(QIcon(":flags/tr.png"),tr("Turkish"),"tr");
    from->addItem(QIcon(":flags/ua.png"),tr("Ukrainian"),"uk");
    from->addItem(QIcon(":flags/vi.png"),tr("Vietnamese"),"vi");
    from->addItem(QIcon(":flags/cy.png"),tr("Welsh"),"cy");
    from->addItem(QIcon(":flags/il.png"),tr("Yiddish"),"yi");
}
void QGoogleTranslator::buildListTo ()
{
    to->addItem(QIcon(":flags/al.png"),tr("Albanian"),"sq");
    to->addItem(QIcon(":flags/ar.png"),tr("Arabic"),"ar");
    to->addItem(QIcon(":flags/eu.png"),tr("Basque"),"eu");
    to->addItem(QIcon(":flags/be.png"),tr("Belarusian"),"be");
    to->addItem(QIcon(":flags/bg.png"),tr("Bulgarian"),"bg");
    to->addItem(QIcon(":flags/ca.png"),tr("Catalan"),"ca");
    to->addItem(QIcon(":flags/cn.png"),tr("Chinese Simplified"),"zh-CN");
    to->addItem(QIcon(":flags/tw.png"),tr("Chinese Traditional"),"zh-TW");
    to->addItem(QIcon(":flags/hr.png"),tr("Croatian"),"hr");
    to->addItem(QIcon(":flags/cz.png"),tr("Czech"),"cs");
    to->addItem(QIcon(":flags/dk.png"),tr("Danish"),"da");
    to->addItem(QIcon(":flags/nl.png"),tr("Dutch"),"nl");
    to->addItem(QIcon(":flags/gb.png"),tr("English"),"en");
    to->addItem(QIcon(":flags/et.png"),tr("Estonian"),"et");
    to->addItem(QIcon(":flags/tl.png"),tr("Filipino"),"tl");
    to->addItem(QIcon(":flags/fi.png"),tr("Finnish"),"fi");
    to->addItem(QIcon(":flags/fr.png"),tr("French"),"fr");
    to->addItem(QIcon(":flags/gl.png"),tr("Galician"),"gl");
    to->addItem(QIcon(":flags/de.png"),tr("German"),"de");
    to->addItem(QIcon(":flags/gr.png"),tr("Greek"),"el");
    to->addItem(QIcon(":flags/ht.png"),tr("Haitian Creole"),"ht");
    to->addItem(QIcon(":flags/il.png"),tr("Hebrew"),"iw");
    to->addItem(QIcon(":flags/in.png"),tr("Hindi"),"hi");
    to->addItem(QIcon(":flags/hu.png"),tr("Hungarian"),"hu");
    to->addItem(QIcon(":flags/is.png"),tr("Icelandic"),"is");
    to->addItem(QIcon(":flags/id.png"),tr("Indonesian"),"id");
    to->addItem(QIcon(":flags/ga.png"),tr("Irish"),"ga");
    to->addItem(QIcon(":flags/it.png"),tr("Italian"),"it");
    to->addItem(QIcon(":flags/jp.png"),tr("Japanese"),"ja");
    to->addItem(QIcon(":flags/lv.png"),tr("Latvian"),"lv");
    to->addItem(QIcon(":flags/lt.png"),tr("Lithuanian"),"lt");
    to->addItem(QIcon(":flags/mk.png"),tr("Macedonian"),"mk");
    to->addItem(QIcon(":flags/ms.png"),tr("Malay"),"ms");
    to->addItem(QIcon(":flags/mt.png"),tr("Maltese"),"mt");
    to->addItem(QIcon(":flags/no.png"),tr("Norwegian"),"no");
    to->addItem(QIcon(":flags/ir.png"),tr("Persian"),"fa");
    to->addItem(QIcon(":flags/pl.png"),tr("Polish"),"pl");
    to->addItem(QIcon(":flags/pt.png"),tr("Portuguese"),"pt");
    to->addItem(QIcon(":flags/ro.png"),tr("Romanian"),"ro");
    to->addItem(QIcon(":flags/ru.png"),tr("Russian"),"ru");
    to->addItem(QIcon(":flags/sr.png"),tr("Serbian"),"sr");
    to->addItem(QIcon(":flags/sk.png"),tr("Slovak"),"sk");
    to->addItem(QIcon(":flags/sl.png"),tr("Slovenian"),"sl");
    to->addItem(QIcon(":flags/es.png"),tr("Spanish"),"es");
    to->addItem(QIcon(":flags/tz.png"),tr("Swahili"),"sw");
    to->addItem(QIcon(":flags/sv.png"),tr("Swedish"),"sv");
    to->addItem(QIcon(":flags/th.png"),tr("Thai"),"th");
    to->addItem(QIcon(":flags/tr.png"),tr("Turkish"),"tr");
    to->addItem(QIcon(":flags/ua.png"),tr("Ukrainian"),"uk");
    to->addItem(QIcon(":flags/vi.png"),tr("Vietnamese"),"vi");
    to->addItem(QIcon(":flags/cy.png"),tr("Welsh"),"cy");
    to->addItem(QIcon(":flags/il.png"),tr("Yiddish"),"yi");
}

void QGoogleTranslator::setDefaultLangs (QString langFrom, QString langTo)
{
    int fromIndex = from->findData (langFrom);
    int toIndex = to->findData (langTo);
    from->setCurrentIndex (fromIndex);
    to->setCurrentIndex (toIndex);
}

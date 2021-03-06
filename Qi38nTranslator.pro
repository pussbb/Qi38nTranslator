#-------------------------------------------------
#
# Project created by QtCreator 2011-05-13T20:59:26
#
#-------------------------------------------------

QT       += core gui network

TARGET = Qi38nTranslator
TEMPLATE = app

unix{
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ./bin/
    UI_DIR = ./obj/
}

TRANSLATIONS = ./lang/qi38ntr_ru.ts \
                ./lang/qi38ntr_def.ts \
                ./lang/qi38ntr_en.ts \


SOURCES += main.cpp\
        src/qi38ntranslator.cpp \
    src/qcorewindow.cpp \
    src/settings.cpp \
    src/qgoogletranslator.cpp \
    qt-json/json.cpp

HEADERS  += headers/qi38ntranslator.h \
    headers/qcorewindow.h \
    headers/settings.h \
    headers/qgoogletranslator.h \
    qt-json/json.h

FORMS    += ui/qi38ntranslator.ui \
    ui/settings.ui

RESOURCES += \
    res/qi38tr.qrc

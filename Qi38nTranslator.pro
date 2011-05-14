#-------------------------------------------------
#
# Project created by QtCreator 2011-05-13T20:59:26
#
#-------------------------------------------------

QT       += core gui

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
    src/qcorewindow.cpp

HEADERS  += headers/qi38ntranslator.h \
    headers/qcorewindow.h

FORMS    += ui/qi38ntranslator.ui

RESOURCES += \
    res/qi38tr.qrc

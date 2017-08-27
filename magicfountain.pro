#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T15:55:51
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = magicfountain
TEMPLATE = app

target.path = /usr/local/bin
INSTALLS += target

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/script.cpp \
    src/block.cpp

INCLUDEPATH += include/
HEADERS  += include/mainwindow.h \
    include/script.h \
    include/block.h

FORMS    += mainwindow.ui

RESOURCES += ressources.qrc

TRANSLATIONS = locales/magicfountain_en.ts locales/magicfountain_fr.ts locales/magicfountain_de.ts

RC_FILE = icon.rc

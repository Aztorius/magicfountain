#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T15:55:51
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicFountain
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    script.cpp \
    block.cpp

HEADERS  += mainwindow.h \
    script.h \
    block.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    ressources.qrc

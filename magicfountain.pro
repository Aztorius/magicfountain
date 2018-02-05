#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T15:55:51
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

TARGET = magicfountain
TEMPLATE = app

mac {
    TARGET = MagicFountain
}

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = magicfountain.desktop
    shortcutfiles.path = $$PREFIX/share/applications/

    desktopicon.files = magicfountain.png
    desktopicon.path = $$PREFIX/share/icons/hicolor/48x48/apps/

    INSTALLS += shortcutfiles
    INSTALLS += desktopicon
}

INSTALLS += target

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/script.cpp \
    src/block.cpp \
    src/scene.cpp \
    src/titlepage.cpp \
    src/titlepageelement.cpp \
    src/title.cpp \
    src/credit.cpp \
    src/author.cpp \
    src/source.cpp \
    src/draftdate.cpp \
    src/contact.cpp \
    src/section.cpp \
    src/act.cpp \
    src/sequence.cpp \
    src/scenesection.cpp \
    src/action.cpp \
    src/synopsis.cpp \
    src/note.cpp \
    src/pagebreak.cpp \
    src/transition.cpp \
    src/lyrics.cpp \
    src/dialogueblock.cpp \
    src/parenthetical.cpp \
    src/dialogue.cpp \
    src/character.cpp \
    src/blankline.cpp \
    src/boneyard.cpp

HEADERS  += src/mainwindow.h \
    src/script.h \
    src/block.h \
    src/scene.h \
    src/titlepage.h \
    src/titlepageelement.h \
    src/title.h \
    src/credit.h \
    src/author.h \
    src/source.h \
    src/draftdate.h \
    src/contact.h \
    src/section.h \
    src/act.h \
    src/sequence.h \
    src/scenesection.h \
    src/action.h \
    src/synopsis.h \
    src/note.h \
    src/pagebreak.h \
    src/transition.h \
    src/lyrics.h \
    src/dialogueblock.h \
    src/parenthetical.h \
    src/dialogue.h \
    src/character.h \
    src/blankline.h \
    src/boneyard.h

FORMS    += mainwindow.ui

RESOURCES += ressources.qrc

TRANSLATIONS = locales/magicfountain_en.ts locales/magicfountain_fr.ts locales/magicfountain_de.ts

RC_FILE = icon.rc

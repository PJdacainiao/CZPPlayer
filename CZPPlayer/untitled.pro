#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T21:15:30
#
#-------------------------------------------------

QT       += core gui
QT       += core gui phonon sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        music.cpp \
    myplaylist.cpp \
    mylistwidget.cpp \
    MusicList.cpp \
    timeindicator.cpp \


HEADERS  += music.h \
    myplaylist.h \
    mylistwidget.h \
    MusicList.h \
    timeindicator.h

RESOURCES += \
    image.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T12:25:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = WordSearch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wordSearch.cpp \
    QTWordSearch.cpp \
    TimeThread.cpp \
    newgame.cpp

HEADERS  += mainwindow.h \
    wordSearch.h \
    QTWordSearch.h \
    TimeThread.h \
    newgame.h

FORMS    += mainwindow.ui \
    newgame.ui

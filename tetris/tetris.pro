QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetris
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        MainWindow.cpp \
    Glass.cpp \
    Figure.cpp

HEADERS  += MainWindow.h \
    Glass.h \
    Figure.h \
    Global.h

FORMS    += MainWindow.ui

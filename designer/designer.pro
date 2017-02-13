QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET = designer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    MyPicture.cpp

HEADERS  += MainWindow.h \
    MyPicture.h

FORMS    += MainWindow.ui

RESOURCES += \
    MyImages.qrc

DISTFILES += \
    designer.rc

RC_FILE=designer.rc

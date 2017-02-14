QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsFrameworkView
TEMPLATE = app
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    MyScene.cpp \
    LineDialog.cpp \
    LineExample.cpp \
    MyRect.cpp \
    MyModel.cpp \
    MyDelegate.cpp

HEADERS  += MainWindow.h \
    MyScene.h \
    LineDialog.h \
    LineExample.h \
    MyRect.h \
    MyModel.h \
    MyDelegate.h \
    MyModelColumns.h

FORMS    += MainWindow.ui \
    LineDialog.ui

RESOURCES += \
    images.qrc

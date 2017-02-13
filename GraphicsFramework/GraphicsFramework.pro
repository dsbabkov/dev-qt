QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsFramework
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    MyScene.cpp \
    LineDialog.cpp \
    LineExample.cpp

HEADERS  += MainWindow.h \
    MyScene.h \
    LineDialog.h \
    LineExample.h

FORMS    += MainWindow.ui \
    LineDialog.ui

RESOURCES += \
    images.qrc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spider
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        Spider.cpp

HEADERS  += Spider.h

TRANSLATIONS += spider_ru.ts

RESOURCES += \
    rsc.qrc

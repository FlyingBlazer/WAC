#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T23:38:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = buaayz-WAC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sampledialog.cpp

HEADERS  += mainwindow.h \
    sampledialog.h

FORMS    += mainwindow.ui \
    sampledialog.ui

CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    .gitignore \
    LICENSE \
    README.md \
    QtApp-debug.apk


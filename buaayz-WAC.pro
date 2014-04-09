#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T23:38:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WAC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sampledialog.cpp \
    sign.cpp \
    settings.cpp \
    login.cpp \
    clientinfo.cpp

HEADERS  += mainwindow.h \
    sampledialog.h \
    sign.h \
    login.h \
    settings.h \
    clientinfo.h

FORMS    += mainwindow.ui \
    sampledialog.ui \
    sign.ui \
    login.ui

CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    .gitignore \
    LICENSE \
    README.md \
    android/AndroidManifest.xml

RESOURCES += \
    res.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

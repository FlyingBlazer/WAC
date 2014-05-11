#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T23:38:26
#
#-------------------------------------------------

QT       += core gui network

android: QT += androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WAC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sampledialog.cpp \
    sign.cpp \
    settings.cpp \
    login.cpp \
    clientinfo.cpp \
    utils.cpp \
    clientinfocollector.cpp \
    selectcar.cpp \
    showclientinfo.cpp \
    touchablescrollarea.cpp

HEADERS  += mainwindow.h \
    sampledialog.h \
    sign.h \
    login.h \
    settings.h \
    clientinfo.h \
    utils.h \
    clientinfocollector.h \
    selectcar.h \
    showclientinfo.h \
    touchablescrollarea.h

FORMS    += mainwindow.ui \
    sampledialog.ui \
    sign.ui \
    login.ui \
    clientinfocollector.ui \
    selectcar.ui \
    showclientinfo.ui

CONFIG += mobility c++11
MOBILITY = 

OTHER_FILES += \
    .gitignore \
    README.md \
    android/AndroidManifest.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png

RESOURCES +=

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

#-------------------------------------------------
#
# Project created by QtCreator 2022-04-26T14:55:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vultr_panel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    linkedlist.cpp \
        main.cpp \
    pagebuy.cpp \
    pageinformation.cpp \
    pagelogin.cpp \
    spider.cpp \
    vpsmodel.cpp \
    vpsos.cpp \
    vultr.cpp

HEADERS += \
    linkedlist.h \
    pagebuy.h \
    pageinformation.h \
    pagelogin.h \
    spider.h \
    vpsmodel.h \
    vpsos.h \
    vultr.h

FORMS += \
    pagebuy.ui \
    pageinformation.ui \
    pagelogin.ui

DISTFILES += \
    readme.md

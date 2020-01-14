
#-------------------------------------------------
#
# Project created by QtCreator 2019-06-03T18:44:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = practice
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    menu.cpp \
    managingspec.cpp \
    signup.cpp \
    apply.cpp \
    recommendation.cpp \
    companyinfo.cpp \
    personalinfo.cpp \
    AvgSpec.cpp \
    PassSpec.cpp \
    Spec.cpp \
    SpecDatabase.cpp \
    UserSpec.cpp

HEADERS += \
        mainwindow.h \
    menu.h \
    managingspec.h \
    signup.h \
    apply.h \
    recommendation.h \
    companyinfo.h \
    personalinfo.h \
    AvgSpec.h \
    PassSpec.h \
    Spec.h \
    SpecDatabase.h \
    UserSpec.h

FORMS += \
        mainwindow.ui \
    menu.ui \
    managingspec.ui \
    signup.ui \
    apply.ui \
    recommendation.ui \
    companyinfo.ui \
    personalinfo.ui

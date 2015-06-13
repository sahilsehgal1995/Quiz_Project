#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T16:15:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sequel
TEMPLATE = app


SOURCES += main.cpp\
        loginpage.cpp \
    questions.cpp \
    settings.cpp

HEADERS  += loginpage.h \
    questions.h \
    settings.h

FORMS    += loginpage.ui \
    questions.ui \
    settings.ui

RESOURCES +=

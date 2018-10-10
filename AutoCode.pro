#-------------------------------------------------
#
# Project created by QtCreator 2018-09-29T08:10:14
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoCode
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    AutoCodeParam.cpp \
    ExcelManager.cpp \
    Method.cpp

HEADERS  += widget.h \
    AutoCodeParam.h \
    ExcelManager.h \
    Method.h

FORMS    += widget.ui

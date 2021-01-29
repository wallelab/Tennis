#-------------------------------------------------
#
# Project created by QtCreator 2021-01-27T08:05:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tennis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cenv.cpp \
    chawk.cpp

HEADERS  += mainwindow.h \
    cenv.h \
    chawk.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/incude

LIBS    +=  -lopencv_core\
            -lopencv_highgui\
            -lopencv_imgproc



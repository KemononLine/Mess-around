#-------------------------------------------------
#
# Project created by QtCreator 2021-8-11T19:56:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
    food.cpp \
    gamecontroller.cpp \
    mainwindow.cpp \
    snake.cpp \


HEADERS  += \
    food.h \
    gamecontroller.h \
    constants.h \
    mainwindow.h \
    snake.h \


RESOURCES += \
    res.qrc

FORMS +=




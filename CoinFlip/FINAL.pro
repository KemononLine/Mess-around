QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooselevelscene.cpp \
    dataconfig.cpp \
    main.cpp \
    mainscene.cpp \
    mycoin.cpp \
    mypushbutton.cpp \
    playscene.cpp

HEADERS += \
    chooselevelscene.h \
    dataconfig.h \
    mainscene.h \
    mycoin.h \
    mypushbutton.h \
    playscene.h

FORMS += \
    mainscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

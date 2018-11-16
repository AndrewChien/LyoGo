#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T11:06:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport

TARGET = LyoGo
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


SOURCES += main.cpp\
        lyogo.cpp \
    login.cpp \
    drawer.cpp \
    widget.cpp \
    messageform.cpp

HEADERS  += lyogo.h \
    login.h \
    connection.h \
    drawer.h \
    widget.h \
    messageform.h

FORMS    += lyogo.ui \
    login.ui \
    widget.ui \
    messageform.ui

RESOURCES += \
    lyogo.qrc

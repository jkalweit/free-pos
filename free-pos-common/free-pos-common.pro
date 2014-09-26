#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T09:30:57
#
#-------------------------------------------------

CONFIG += c++11

QT       += qml

QT       -= gui

TARGET = free-pos-common
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    MenuCategory.cpp \
    FreePosCommand.cpp \
    Menu.cpp \
    MenuItem.cpp

HEADERS += \
    MenuCategory.h \
    FreePosCommand.h \
    SimpleSerializable.h \
    Menu.h \
    MenuItem.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T09:30:57
#
#-------------------------------------------------

CONFIG += c++11 printsupport

QT       += qml printsupport

QT       -= gui

TARGET = free-pos-common
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    MenuCategory.cpp \
    FreePosCommand.cpp \
    Menu.cpp \
    MenuItem.cpp \
    Customer.cpp \
    Ticket.cpp \
    Reconciliation.cpp \
    OrderItem.cpp \
    CashDrawer.cpp \
    Pos.cpp \
    SimpleSerializable.cpp \
    InventoryItem.cpp \
    Inventory.cpp

HEADERS += \
    MenuCategory.h \
    FreePosCommand.h \
    SimpleSerializable.h \
    Menu.h \
    MenuItem.h \
    Customer.h \
    Ticket.h \
    Reconciliation.h \
    OrderItem.h \
    CashDrawer.h \
    Pos.h \
    InventoryItem.h \
    Inventory.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

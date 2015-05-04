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
    Inventory.cpp \
    MenuItemInventoryItem.cpp \
    OrderItemInventoryItem.cpp \
    MenuItemOption.cpp \
    OrderItemOption.cpp \
    DayTracker.cpp \
    WeekTracker.cpp \
    Cost.cpp \
    EmployeeShift.cpp \
    EmployeeShiftsSummary.cpp \
    LoyaltyMember.cpp \
    WebServiceController.cpp

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
    Inventory.h \
    MenuItemInventoryItem.h \
    OrderItemInventoryItem.h \
    MenuItemOption.h \
    OrderItemOption.h \
    DayTracker.h \
    WeekTracker.h \
    Cost.h \
    EmployeeShift.h \
    EmployeeShiftsSummary.h \
    LoyaltyMember.h \
    WebServiceController.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

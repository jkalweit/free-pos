#include "SimpleSerializable.h"

#include "Pos.h"

SimpleSerializable::SimpleSerializable(QObject *parent) :
    QObject(parent)
{
}

void SimpleSerializable::logPropertyChanged(QVariant value, QString propertyName) {
    if(Pos::instance()) {
        Pos::instance()->appendToHistory(serializeList(updatePrefix() << propertyName << escapeString(value.toString())));
    }
}

void SimpleSerializable::logMenuPropertyChanged(QVariant value, QString propertyName) {
    Pos::instance()->appendToMenuHistory(serializeList(updatePrefix() << propertyName << escapeString(value.toString())));
}

void SimpleSerializable::logInventoryPropertyChanged(QVariant value, QString propertyName) {
    Pos::instance()->appendToInventoryHistory(serializeList(updatePrefix() << propertyName << escapeString(value.toString())));
}

void SimpleSerializable::logTrackerPropertyChanged(QVariant value, QString propertyName) {
    Pos::instance()->appendToTrackerHistory(serializeList(updatePrefix() << propertyName << escapeString(value.toString())));
}

void SimpleSerializable::logFixedCostPropertyChanged(QVariant value, QString propertyName) {
    Pos::instance()->appendToFixedCostHistory(serializeList(updatePrefix() << propertyName << escapeString(value.toString())));
}

QString SimpleSerializable::escapeString(QString val) {
    return val.replace("\n", "\\n").replace(":", "\\!");
}

QString SimpleSerializable::unEscapeString(QString val) {
    return val.replace("\\n", "\n").replace("\\!", ":");
}

QString SimpleSerializable::serializeList(QStringList vals) {
    QString result = "";
    for(QString val : vals) {
        if(result != "")
            result += ":";
        result += escapeString(val);
    }
    return result;
}

QStringList SimpleSerializable::deserializeList(QString vals) {
    QStringList input = vals.split(":");
    QStringList result;
    for(QString val : input) {
        result << unEscapeString(val);
    }
    return result;
}

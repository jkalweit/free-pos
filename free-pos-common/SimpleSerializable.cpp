#include "SimpleSerializable.h"

SimpleSerializable::SimpleSerializable(QObject *parent) :
    QObject(parent)
{
}

QString SimpleSerializable::escapeString(QString val) {
    return val.replace("\n", "\\n").replace(":", "\\colon");
}

QString SimpleSerializable::unEscapeString(QString val) {
    return val.replace("\\n", "\n").replace("\\colon", ":");
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
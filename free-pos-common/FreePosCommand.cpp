#include "FreePosCommand.h"

#include <QDebug>

const QString FreePosCommand::MENU_GET_CATEGORIES = "MenuGetCategories";
const QString FreePosCommand::MENU_ADD_CATEGORY = "MenuAddCategory";
const QString FreePosCommand::MENU_ADD_ITEM = "MenuAddItem";

FreePosCommand::FreePosCommand(QString command)
    : m_command(command)
{

}

QString FreePosCommand::command() {
    return m_command;
}

QString FreePosCommand::serialize() const {
    return m_command;
}

FreePosCommand FreePosCommand::deserialize(QString serialized)
{
    //QStringList split = serialized.split(":");

    //quint32 id = split[0].toInt();
    //QString name = split[1];

    FreePosCommand obj(serialized);
    qDebug() << "    deserialized: " << obj.serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const FreePosCommand& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, FreePosCommand& obj) {

    QString line = stream.readAll();
    FreePosCommand m = FreePosCommand::deserialize(line);
    obj.m_command = m.m_command;

    return stream;
}





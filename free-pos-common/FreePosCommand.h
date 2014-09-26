#ifndef FREEPOSCOMMAND_H
#define FREEPOSCOMMAND_H

#include <QTextStream>
#include <QString>

class FreePosCommand
{


public:
    static const QString MENU_GET_CATEGORIES;
    static const QString MENU_ADD_CATEGORY;
    static const QString MENU_ADD_ITEM;

    explicit FreePosCommand(QString command = "");    

    QString command();

    QString serialize() const;
    static FreePosCommand deserialize(QString serialized);

    friend QTextStream& operator<<(QTextStream& stream, const FreePosCommand& obj);
    friend QTextStream& operator>>(QTextStream& stream, FreePosCommand& obj);

private:
    QString m_command;
};

#endif // FREEPOSCOMMAND_H

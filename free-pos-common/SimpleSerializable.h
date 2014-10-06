#ifndef SIMPLESERIALIZABLE_H
#define SIMPLESERIALIZABLE_H

#include <QStringList>
#include <QObject>

class SimpleSerializable : public QObject
{
    Q_OBJECT
public:
    explicit SimpleSerializable(QObject *parent = 0);
    static QString escapeString(QString val);
    static QString unEscapeString(QString val);
    static QString serializeList(QStringList vals);
    static QStringList deserializeList(QString vals);
signals:

public slots:

};

#endif // SIMPLESERIALIZABLE_H

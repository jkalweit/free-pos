#ifndef DAILYCOST_H
#define DAILYCOST_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class DailyCost : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
public:
    explicit DailyCost(QObject *parent = 0, quint32 id = 0, QString name = "");

    quint32 id();
    float cost();


signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void costChanged(float);

public slots:

private:
    quint32 m_id;
    QString m_name;

};

#endif // DAILYCOST_H

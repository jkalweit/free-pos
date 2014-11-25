#ifndef FIXEDCOST_H
#define FIXEDCOST_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class FixedCost : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(float cost MEMBER m_cost READ cost WRITE setCost NOTIFY costChanged)
public:
    explicit FixedCost(QObject *parent = 0, quint32 id = 0, QString name = "", QString type = "", float cost = 0);

    quint32 id();
    QString name();
    QString type();
    float cost();

    void setName(QString value);
    void setType(QString value);
    void setCost(float value);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void typeChanged(QString);
    void costChanged(float);

public slots:

private:
    quint32 m_id;
    QString m_name;
    QString m_type;
    float m_cost;

};

#endif // FIXEDCOST_H

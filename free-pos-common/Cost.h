#ifndef COST_H
#define COST_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class Cost : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(float cost MEMBER m_cost READ cost NOTIFY costChanged)

public:
    explicit Cost(QObject *parent = 0, quint32 id = 0, QString name = "", float cost = 0);

    virtual QStringList updatePrefix();

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
    float m_cost;


};

#endif // COST_H

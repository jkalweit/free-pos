#ifndef ORDERITEMOPTION_H
#define ORDERITEMOPTION_H

#include <QObject>
#include "SimpleSerializable.h"

class OrderItemOption : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 ticketId MEMBER m_ticketId WRITE setTicketId NOTIFY ticketIdChanged)
    Q_PROPERTY(quint32 customerId MEMBER m_customerId WRITE setCustomerId NOTIFY customerIdChanged)
    Q_PROPERTY(quint32 orderItemId MEMBER m_orderItemId NOTIFY orderItemIdChanged)
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float cost MEMBER m_cost WRITE setCost NOTIFY costChanged)
public:
    explicit OrderItemOption(QObject *parent = 0, quint32 ticketId = 0, quint32 customerId = 0, quint32 orderItemId = 0, quint32 id = 0, QString name = "", float cost = 0);

    virtual QStringList updatePrefix();

    QString serialize() const;
    static OrderItemOption* deserialize(QString serialized, QObject *parent = 0);


signals:
    void ticketIdChanged(quint32);
    void customerIdChanged(quint32);
    void orderItemIdChanged(quint32);
    void idChanged(quint32);
    void nameChanged(QString);
    void costChanged(float);

public slots:

private:
    quint32 m_ticketId;
    quint32 m_customerId;
    quint32 m_orderItemId;
    quint32 m_id;
    QString m_name;
    float m_cost;
};

#endif // ORDERITEMOPTION_H

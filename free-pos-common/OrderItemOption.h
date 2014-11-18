#ifndef ORDERITEMOPTION_H
#define ORDERITEMOPTION_H

#include <QObject>
#include "SimpleSerializable.h"

class OrderItemOption : public SimpleSerializable
{
    Q_OBJECT
//    Q_PROPERTY(quint32 ticketId MEMBER m_ticketId WRITE setTicketId NOTIFY ticketIdChanged)
//    Q_PROPERTY(quint32 customerId MEMBER m_customerId WRITE setCustomerId NOTIFY customerIdChanged)
//    Q_PROPERTY(quint32 orderItemId MEMBER m_orderItemId NOTIFY orderItemIdChanged)
//    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(quint32 optionMenuCategoryId MEMBER m_optionMenuCategoryId NOTIFY optionMenuCategoryIdChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString menuItemName MEMBER m_menuItemName WRITE setMenuItemName NOTIFY menuItemNameChanged)
    Q_PROPERTY(float cost MEMBER m_cost READ cost WRITE setCost NOTIFY costChanged)
public:
    explicit OrderItemOption(QObject *parent = 0, quint32 ticketId = 0, quint32 customerId = 0, quint32 orderItemId = 0, quint32 id = 0, quint32 optionMenuCategoryId = 0, QString name = "", QString menuItemName = "", float cost = 0);

    virtual QStringList updatePrefix();

    quint32 ticketId();
    quint32 customerId();
    quint32 orderItemId();
    quint32 id();
    float cost();

    void setName(QString name);
    void setMenuItemName(QString menuItemName);
    void setCost(float cost);

    QString serialize() const;
    static OrderItemOption* deserialize(QString serialized, QObject *parent = 0);


signals:
//    void ticketIdChanged(quint32);
//    void customerIdChanged(quint32);
//    void orderItemIdChanged(quint32);
//    void idChanged(quint32);
    void optionMenuCategoryIdChanged(quint32);
    void nameChanged(QString);
    void menuItemNameChanged(QString);
    void costChanged(float);

public slots:

private:
    quint32 m_ticketId;
    quint32 m_customerId;
    quint32 m_orderItemId;
    quint32 m_id;
    quint32 m_optionMenuCategoryId;
    QString m_name;
    QString m_menuItemName;
    float m_cost;
};

#endif // ORDERITEMOPTION_H

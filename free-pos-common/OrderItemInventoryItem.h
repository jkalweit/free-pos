#ifndef ORDERITEMINVENTORYITEM_H
#define ORDERITEMINVENTORYITEM_H

#include <QTextStream>
#include <QObject>
#include "SimpleSerializable.h"

class OrderItemInventoryItem : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(quint32 inventoryItemId MEMBER m_inventoryItemId NOTIFY inventoryItemIdChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(float price MEMBER m_price NOTIFY priceChanged)
    Q_PROPERTY(float quantity MEMBER m_quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
public:
    explicit OrderItemInventoryItem(QObject *parent = 0, quint32 ticketId = 0, quint32 customerId = 0, quint32 orderItemId = 0, quint32 id = 0, quint32 inventoryItemId = 0, QString name = "", float price = 0, float quantity = 0);

    virtual QStringList updatePrefix();

    void setQuantity(float quantity);
    float cost();

    quint32 ticketId();
    quint32 customerId();
    quint32 orderItemId();
    quint32 id();

    QString serialize() const;
    static OrderItemInventoryItem* deserialize(QString serialized, QObject *parent = 0);


signals:
    void idChanged(quint32);
    void inventoryItemIdChanged(quint32);
    void nameChanged(QString);
    void priceChanged(float);
    void quantityChanged(float);
    void costChanged(float);

public slots:
    void fireCostChanged();

private:
    quint32 m_ticketId;
    quint32 m_customerId;
    quint32 m_orderItemId;
    quint32 m_id;
    quint32 m_inventoryItemId;
    QString m_name;
    float m_price;
    float m_quantity;



};

#endif // ORDERITEMINVENTORYITEM_H

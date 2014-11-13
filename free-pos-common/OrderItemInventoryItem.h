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
    Q_PROPERTY(QString unit MEMBER m_unit NOTIFY unitChanged)
    Q_PROPERTY(float price MEMBER m_price NOTIFY priceChanged)
    Q_PROPERTY(float quantity MEMBER m_quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
    Q_PROPERTY(bool isRemoved MEMBER m_isRemoved WRITE setIsRemoved NOTIFY isRemovedChanged)
    Q_PROPERTY(bool isAdded MEMBER m_isAdded WRITE setIsAdded NOTIFY isAddedChanged)
public:
    explicit OrderItemInventoryItem(QObject *parent = 0, quint32 ticketId = 0, quint32 customerId = 0, quint32 orderItemId = 0, quint32 id = 0, quint32 inventoryItemId = 0, QString name = "", QString unit = "", float price = 0, float quantity = 0, bool isRemoved = false, bool isAdded = false);

    virtual QStringList updatePrefix();

    void setQuantity(float quantity);
    void setIsRemoved(bool isRemoved);
    void setIsAdded(bool isAdded);
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
    void unitChanged(QString);
    void priceChanged(float);
    void quantityChanged(float);
    void costChanged(float);
    void isRemovedChanged(bool);
    void isAddedChanged(bool);

public slots:
    void fireCostChanged();

private:
    quint32 m_ticketId;
    quint32 m_customerId;
    quint32 m_orderItemId;
    quint32 m_id;
    quint32 m_inventoryItemId;
    QString m_name;
    QString m_unit;
    float m_price;
    float m_quantity;
    bool m_isRemoved;
    bool m_isAdded;

};

#endif // ORDERITEMINVENTORYITEM_H

#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class InventoryItem : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString unit MEMBER m_unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(float defaultQuantity MEMBER m_defaultQuantity WRITE setDefaultQuantity NOTIFY defaultQuantityChanged)
    Q_PROPERTY(float priceQuantity MEMBER m_priceQuantity WRITE setPriceQuantity NOTIFY priceQuantityChanged)
    Q_PROPERTY(float price MEMBER m_price WRITE setPrice NOTIFY priceChanged)

    Q_PROPERTY(float unitPrice READ unitPrice NOTIFY unitPriceChanged)
    Q_PROPERTY(float defaultCost READ defaultCost NOTIFY defaultCostChanged)

public:
    explicit InventoryItem(QObject *parent = 0, quint32 id = 0, QString name = "", QString unit = "", float defaultQuantity = 0, float priceQuantity = 0, float price = 0);

    virtual QStringList updatePrefix();

    void setName(QString name);
    void setUnit(QString unit);
    void setDefaultQuantity(float defaultQuantity);
    void setPriceQuantity(float priceQuantity);
    void setPrice(float price);

    float unitPrice();
    float defaultCost();

    QString serialize() const;
    static InventoryItem* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void unitChanged(QString);
    void defaultQuantityChanged(float);
    void priceQuantityChanged(float);
    void priceChanged(float);

    void unitPriceChanged(float);
    void defaultCostChanged(float);
public slots:

private:
    quint32 m_id;
    QString m_name;
    QString m_unit;
    float m_defaultQuantity;
    float m_priceQuantity;
    float m_price;
};

#endif // INVENTORYITEM_H

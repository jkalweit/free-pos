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
    Q_PROPERTY(float price MEMBER m_price WRITE setPrice NOTIFY priceChanged)
public:
    explicit InventoryItem(QObject *parent = 0, quint32 id = 0, QString name = "", float price = 0);

    virtual QStringList updatePrefix();

    void setName(QString name);
    void setPrice(float price);

    QString serialize() const;
    static InventoryItem* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void priceChanged(float);

public slots:

private:
    quint32 m_id;
    QString m_name;
    float m_price;
};

#endif // INVENTORYITEM_H

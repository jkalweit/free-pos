#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "OrderItem.h"


class Customer : public SimpleSerializable {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(quint32 ticketId MEMBER m_ticketId NOTIFY ticketIdChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<OrderItem> orderItems READ orderItems NOTIFY orderItemsChanged)

    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit Customer(QObject *parent = 0, quint32 id = 0, quint32 ticketId = 0, QString name = "");

    void setName(QString name);

    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    QQmlListProperty<OrderItem> orderItems();
    Q_INVOKABLE OrderItem* addOrderItem(QString name, QString type, float price, float quantity, QString note);
    void addOrderItem(OrderItem *orderItem);
    OrderItem* getOrderItem(quint32 id);

    QString serialize() const;
    static Customer* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void ticketIdChanged(quint32);
    void nameChanged(QString);
    void orderItemsChanged(QQmlListProperty<OrderItem>);

    void foodTotalChanged(float);
    void taxTotalChanged(float);
    void barTotalChanged(float);
    void totalChanged(float);

private:
    quint32 m_id;
    quint32 m_ticketId;
    QString m_name;
    QList<OrderItem*> m_orderItems;

    quint32 m_currentOrderItemId;


private slots:
    void fireTotalsChanged();
    void logPropertyChanged(QVariant value, QString propertyName);
};

#endif // CUSTOMER_H

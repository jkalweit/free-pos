#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "OrderItem.h"
#include "MenuItem.h"


class Customer : public SimpleSerializable {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(quint32 ticketId MEMBER m_ticketId NOTIFY ticketIdChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString loyaltyMemberId MEMBER m_loyaltyMemberId WRITE setLoyaltyMemberId NOTIFY loyaltyMemberIdChanged)
    Q_PROPERTY(QQmlListProperty<OrderItem> orderItems READ orderItems NOTIFY orderItemsChanged)
    Q_PROPERTY(bool isLoyaltyMember READ isLoyaltyMember NOTIFY isLoyaltyMemberChanged)

    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)

    Q_PROPERTY(float actualTax READ actualTax NOTIFY actualTaxChanged)
    Q_PROPERTY(float cog READ cog NOTIFY cogChanged)
    Q_PROPERTY(float margin READ margin NOTIFY marginChanged)
public:
    explicit Customer(QObject *parent = 0, quint32 id = 0, quint32 ticketId = 0, QString name = "", QString loyaltyMemberId = "");

    virtual QStringList updatePrefix();

    void setName(QString name);
    void setLoyaltyMemberId(QString loyaltyMemberId);

    bool isLoyaltyMember();

    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    float actualTax();
    float cog();
    float margin();

    QQmlListProperty<OrderItem> orderItems();
    Q_INVOKABLE OrderItem* addOrderItem(MenuItem *menuItem, float quantity, QString note);
    void addOrderItem(OrderItem *orderItem, bool isMoved = false);
    OrderItem* getOrderItem(quint32 id);
    QList<OrderItem*> orderItemsList();   
    Q_INVOKABLE void removeOrderItem(OrderItem* orderItem);

    QString serialize() const;
    static Customer* deserialize(QString serialized, QObject *parent = 0);          

signals:
    void idChanged(quint32);
    void ticketIdChanged(quint32);
    void nameChanged(QString);
    void loyaltyMemberIdChanged(QString);
    void orderItemsChanged(QQmlListProperty<OrderItem>);

    void foodTotalChanged(float);
    void taxTotalChanged(float);
    void barTotalChanged(float);
    void totalChanged(float);

    void actualTaxChanged(float);
    void cogChanged(float);
    void marginChanged(float);

    void isLoyaltyMemberChanged(bool);

private:
    quint32 m_id;
    quint32 m_ticketId;
    QString m_name;
    QString m_loyaltyMemberId;
    QList<OrderItem*> m_orderItems;

    quint32 m_currentOrderItemId;


private slots:
    void fireCogChanged();
    void fireTotalsChanged();    
};

#endif // CUSTOMER_H

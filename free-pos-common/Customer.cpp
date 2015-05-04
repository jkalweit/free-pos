#include "Customer.h"

#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"
#include "MenuItemInventoryItem.h"
#include "MenuItemOption.h"

Customer::Customer(QObject *parent, quint32 id, quint32 ticketId, QString name, QString loyaltyMemberId) :
    SimpleSerializable(parent), m_id(id), m_ticketId(ticketId), m_name(name), m_loyaltyMemberId(loyaltyMemberId), m_currentOrderItemId(0)
{
}


QStringList Customer::updatePrefix() {
    return QStringList() << "UpdateCustomer" << QString::number(m_ticketId) << QString::number(m_id);
}


void Customer::setName(QString name) {
    QString normalized = name.toUpper().trimmed();
    if(m_name != normalized) {
        m_name = normalized;
        logPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void Customer::setLoyaltyMemberId(QString id) {
    if(m_loyaltyMemberId != id) {
        m_loyaltyMemberId = id;
        logPropertyChanged(m_loyaltyMemberId, "loyaltyMemberId");
        loyaltyMemberIdChanged(m_loyaltyMemberId);
        isLoyaltyMemberChanged(isLoyaltyMember());
    }
}

bool Customer::isLoyaltyMember() {
    return m_loyaltyMemberId != "";
}

float Customer::foodTotal() {
    float sum = 0;
    QString type;
    for(OrderItem *o : m_orderItems) {
        type = o->property("type").toString();
        if(!o->isAlcohol()) {
            sum += o->subTotal();
        }
    }
    return sum;
}

float Customer::taxTotal() {
    return foodTotal() * 0.09;
}

float Customer::barTotal() {
    float sum = 0;
    for(OrderItem *o : m_orderItems) {        
        if(o->isAlcohol()) {
            sum += o->subTotal();
        }
    }
    return sum;
}

float Customer::total() {
    return foodTotal() + taxTotal() + barTotal();
}




void Customer::fireCogChanged() {
    cogChanged(cog());
    marginChanged(margin());
}

void Customer::fireTotalsChanged() {
    foodTotalChanged(foodTotal());
    taxTotalChanged(taxTotal());
    barTotalChanged(barTotal());
    totalChanged(total());

    actualTaxChanged(actualTax());
    marginChanged(margin());
}



float Customer::actualTax() {
    float total = 0;

    for(OrderItem *item : m_orderItems) {
        total += item->actualTax();
    }

    return total;
}

float Customer::cog() {
    float total = 0;

    for(OrderItem *item : m_orderItems) {
        total += item->cog();
    }

    return total;
}

float Customer::margin() {
    float total = 0;

    for(OrderItem *item : m_orderItems) {
        total += item->margin();
    }

    return total;
}



OrderItem* Customer::addOrderItem(MenuItem* menuItem, float quantity, QString note) {
    OrderItem* orderItem = new OrderItem(this, ++m_currentOrderItemId, m_ticketId, m_id,
                                         menuItem->property("name").toString(),
                                         menuItem->property("type").toString(),
                                         QDateTime::currentDateTime(),
                                         menuItem->property("price").toFloat(), quantity, note, false);

    addOrderItem(orderItem);
    if(menuItem->property("type").toString() == "Alcohol" && !orderItem->isSubmitted()) {
        orderItem->setSubmittedStamp(orderItem->property("createdStamp").toDateTime());
    }

    // add OrderItemInventoryItems AFTER adding OrderItem to ensure correct order of events in History.
    for(MenuItemInventoryItem *item : menuItem->menuItemInventoryItemsList()) {
        orderItem->addOrderItemInventoryItem(item->property("inventoryItemId").toUInt(),
                                             item->inventoryItem()->property("name").toString(),
                                             item->inventoryItem()->property("unit").toString(),
                                             item->inventoryItem()->unitPrice(),
                                             item->property("quantity").toFloat());
    }

    for(MenuItemOption *item : menuItem->menuItemOptionsList()) {
        quint32 optionMenuCategoryId = item->property("optionMenuCategoryId").toUInt();
        orderItem->addOrderItemOption(optionMenuCategoryId);
    }

    return orderItem;
}

void Customer::addOrderItem(OrderItem *orderItem, bool isMoved) {
    if(orderItem->property("id").toUInt() > m_currentOrderItemId) m_currentOrderItemId = orderItem->property("id").toUInt();
//    connect(orderItem, SIGNAL(subTotalChanged(float)),
//            this, SLOT(fireTotalsChanged()));
//    connect(orderItem, SIGNAL(taxChanged(float)),
//            this, SLOT(fireTotalsChanged()));
    connect(orderItem, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));

    connect(orderItem, SIGNAL(cogChanged(float)),
            this, SLOT(fireCogChanged()));
//    connect(orderItem, SIGNAL(marginChanged(float)),
//            this, SLOT(fireTotalsChanged()));

    m_orderItems.append(orderItem);
    if(!isMoved) {
        Pos::instance()->appendToHistory("AddOrderItem:" + orderItem->serialize());
    }
    orderItemsChanged(orderItems());
    fireTotalsChanged();
}

QQmlListProperty<OrderItem> Customer::orderItems() {
    return QQmlListProperty<OrderItem>(this, m_orderItems);
}

OrderItem* Customer::getOrderItem(quint32 id) {
    for(OrderItem* item : m_orderItems) {
        if(item->property("id").toUInt() == id){
            return item;
        }
    }
    return nullptr;
}

QList<OrderItem*> Customer::orderItemsList() {
    return m_orderItems;
}

void Customer::removeOrderItem(OrderItem *orderItem) {
    for(int i = 0; i < m_orderItems.length(); i++) {
        if(m_orderItems[i] == orderItem) {
            m_orderItems.removeAt(i);
            orderItemsChanged(orderItems());
            fireCogChanged();
            fireTotalsChanged();
            return;
        }
    }
}

QString Customer::serialize() const {
    return QString::number(m_id) + ":" + QString::number(m_ticketId) + ":" + m_name + ":" + m_loyaltyMemberId;
}

Customer* Customer::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    quint32 ticketId = split[1].toInt();
    QString name = split[2];
    QString loyaltyMemberId = "";
    if(split.length() > 3) {
        loyaltyMemberId = split[3];
    }

    Customer *obj = new Customer(parent, id, ticketId, name, loyaltyMemberId);
    return obj;
}





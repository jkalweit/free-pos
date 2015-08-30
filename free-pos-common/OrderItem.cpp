#include <QMetaProperty>
#include <QDebug>
#include "OrderItem.h"
#include "Pos.h"

OrderItem::OrderItem(QObject *parent, quint32 id, quint32 ticketId, quint32 customerId, QString name, QString type, QDateTime createdStamp, float price, float quantity, QString note, bool deleted, QDateTime submittedStamp, bool isHiddenFromKitchen, QString prepType) :
    SimpleSerializable(parent), m_id(id), m_ticketId(ticketId), m_customerId(customerId), m_name(name), m_type(type), m_createdStamp(createdStamp), m_price(price), m_quantity(quantity), m_note(note), m_deleted(deleted), m_submittedStamp(submittedStamp), m_currentOrderItemInventoryItemId(0), m_currentOrderItemOptionId(0), m_isHiddenFromKitchen(isHiddenFromKitchen), m_prepType(prepType)
{
}

QStringList OrderItem::updatePrefix() {
    return QStringList() << "UpdateOrderItem" << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_id);
}

void OrderItem::setTicketId(quint32 ticketId) {
    if(m_ticketId != ticketId) {
        m_ticketId = ticketId;
        logPropertyChanged(m_ticketId, "ticketId");
        ticketIdChanged(m_ticketId);
    }
}

void OrderItem::setCustomerId(quint32 customerId) {
    if(m_customerId != customerId) {
        m_customerId = customerId;
        logPropertyChanged(m_customerId, "customerId");
        customerIdChanged(m_customerId);
    }
}

void OrderItem::setCreatedStamp(QDateTime createdStamp) {
    if(m_createdStamp != createdStamp){
        m_createdStamp = createdStamp;
        logPropertyChanged(m_createdStamp, "createdStamp");
        createdStampChanged(m_createdStamp);
    }
}

void OrderItem::setQuantity(float quantity) {
    if(m_quantity != quantity) {
        m_quantity = quantity;
        logPropertyChanged(m_quantity, "quantity");
        quantityChanged(m_quantity);
        fireCogChanged();
        fireTotalsChanged();        
    }
}

void OrderItem::setPrice(float price) {
    if(m_price != price) {
        m_price = price;
        logPropertyChanged(m_price, "price");
        priceChanged(m_price);
        fireTotalsChanged();
    }
}

void OrderItem::setNote(QString note) {
    if(m_note != note) {
        m_note = note;
        logPropertyChanged(m_note, "note");
        noteChanged(m_note);
    }
}

void OrderItem::setDeleted(bool deleted) {
    if(m_deleted != deleted) {
        m_deleted = deleted;
        logPropertyChanged(m_deleted, "deleted");
        deletedChanged(m_deleted);
        fireTotalsChanged();
    }
}

void OrderItem::setSubmittedStamp(QDateTime submittedStamp) {
    if(m_submittedStamp != submittedStamp){
        m_submittedStamp = submittedStamp;
        logPropertyChanged(m_submittedStamp, "submittedStamp");
        submittedStampChanged(m_submittedStamp);
        isSubmittedChanged(isSubmitted());
    }
}

void OrderItem::setPrepType(QString prepType) {
    if(m_prepType != prepType){
        m_prepType = prepType;
        logPropertyChanged(m_prepType, "prepType");
        prepTypeChanged(m_prepType);
    }
}



bool OrderItem::isSubmitted() {
    return m_submittedStamp.isValid();
}

void OrderItem::cycleSubmittedStamp() {
    if(m_submittedStamp.isValid()) {
        setSubmittedStamp(QDateTime());
    } else {
        setSubmittedStamp(QDateTime::currentDateTime());
    }
}

bool OrderItem::isAlcohol() {
    return m_type == "Alcohol";
}

bool OrderItem::isHiddenFromKitchen() {
    return m_isHiddenFromKitchen;
}

QString OrderItem::prepType() {
    return m_prepType;
}




void OrderItem::fireCogChanged() {
    cogChanged(cog());
    // TODO: costChanged(cost());
    marginChanged(margin());
}

void OrderItem::fireTotalsChanged() {
    subTotalChanged(subTotal());
    taxChanged(tax());
    totalChanged(total());

    actualTaxChanged(actualTax());
    // TODO: costChanged(cost());
    marginChanged(margin());
}






float OrderItem::subTotal() {
    if(m_deleted)
        return 0;
    else
        return (m_quantity * m_price);
}

float OrderItem::tax() {
    if(m_type == "Alcohol" || m_type == "Food - Tax Included") {
        return 0;
    } else {
        return subTotal() * 0.09;
    }
}

float OrderItem::total() {
    return subTotal() + tax();
}




float OrderItem::actualTax() {
    // This is the Tax PAID by the company, where as tax() is the Tax shown on the receipt,
    //      for items that don't include the tax in the price (in our case: none-alcohol items)
    // TODO: Include Liquor Tax?
    // 0.09 = 0.06 state sales + 0.01 capital projects + 0.02 city hospitality
    return subTotal() * 0.09;
}

float OrderItem::cog() {

    if(m_deleted) {
        return 0;
    }

    float cost = 0;

    for(OrderItemInventoryItem *item : m_orderItemInventoryItems) {
        cost += (m_quantity * item->cost());
    }

    for(OrderItemOption *item : m_orderItemOptions) {
        cost += (m_quantity * item->cost());
    }

    return cost;
}

float OrderItem::margin() {
    return subTotal() - cog() - actualTax();  // m_deleted case handled in subTotal() and cost()
}






float OrderItem::getCumulativeCostUpToOption(quint32 orderItemOptionId) {

    float cost = 0;

    for(OrderItemOption *item : m_orderItemOptions) {
        if(orderItemOptionId == item->id()) {
            return cost;
        }
        cost += item->cost();
    }

    // should only get this far when passing invalid id, such as -1 to get total option cost.
    return cost;
}


float OrderItem::getCumulativeCostUpToInventoryItem(quint32 inventoryItemId) {

    float cost = getCumulativeCostUpToOption(-1); // get cost of all options

    for(OrderItemInventoryItem *item : m_orderItemInventoryItems) {
        if(inventoryItemId == item->id()) {
            return cost;
        }
        cost += item->cost();
    }

    // should only get this far when passing invalid id, such as -1 to get total cost.
    return cost;
}








OrderItemInventoryItem* OrderItem::addOrderItemInventoryItem(quint32 inventoryItemId, QString name, QString unit, float price, float quantity) {
    OrderItemInventoryItem* item = new OrderItemInventoryItem(this, m_ticketId, m_customerId, m_id, ++m_currentOrderItemInventoryItemId, inventoryItemId, name, unit, price, quantity);
    addOrderItemInventoryItem(item);
    return item;
}

void OrderItem::addOrderItemInventoryItem(OrderItemInventoryItem *orderItemInventoryItem) {
    if(orderItemInventoryItem->property("id").toUInt() > m_currentOrderItemInventoryItemId) m_currentOrderItemInventoryItemId = orderItemInventoryItem->property("id").toUInt();

    m_orderItemInventoryItems.append(orderItemInventoryItem);
    connect(orderItemInventoryItem, SIGNAL(costChanged(float)),
            this, SLOT(fireCogChanged()));

    Pos::instance()->appendToHistory("AddOrderItemInventoryItem:" + orderItemInventoryItem->serialize());
    orderItemInventoryItemsChanged(orderItemInventoryItems());
    fireCogChanged();
}

QQmlListProperty<OrderItemInventoryItem> OrderItem::orderItemInventoryItems() {
    return QQmlListProperty<OrderItemInventoryItem>(this, m_orderItemInventoryItems);
}

QList<OrderItemInventoryItem*> OrderItem::orderItemInventoryItemsList() {
    return m_orderItemInventoryItems;
}

OrderItemInventoryItem* OrderItem::getOrderItemInventoryItem(quint32 id) {
    for(OrderItemInventoryItem* item : m_orderItemInventoryItems) {
        if(item->property("id").toUInt() == id){
            return item;
        }
    }
    return nullptr;
}

void OrderItem::removeOrderItemInventoryItem(quint32 id) {
    for(int i = 0; i < m_orderItemInventoryItems.length(); i++) {
        if(m_orderItemInventoryItems[i]->property("id").toUInt() == id) {
            OrderItemInventoryItem *item = m_orderItemInventoryItems[i];
            m_orderItemInventoryItems.removeAt(i);
            disconnect(item, SIGNAL(costChanged(float)),
                       this, SLOT(fireCogChanged()));
            QStringList historyEntry;
            historyEntry << "RemoveOrderItemInventoryItem" << item->property("ticketId").toString() << item->property("customerId").toString() << item->property("orderItemId").toString() << item->property("id").toString();
            Pos::instance()->appendToHistory(serializeList(historyEntry));
            orderItemInventoryItemsChanged(orderItemInventoryItems());
            fireCogChanged();
            return;
        }
    }
}







OrderItemOption* OrderItem::addOrderItemOption(quint32 optionMenuCategoryId) {
    QString name = Pos::instance()->selectedMenu()->getMenuCategory(optionMenuCategoryId)->property("name").toString();
    OrderItemOption *item = new OrderItemOption(this, m_ticketId, m_customerId, m_id, ++m_currentOrderItemOptionId, optionMenuCategoryId, name, "", 0);
    addOrderItemOption(item);
    return item;
}

void OrderItem::addOrderItemOption(OrderItemOption *orderItemOption) {
    if(orderItemOption->id() > m_currentOrderItemOptionId) m_currentOrderItemOptionId = orderItemOption->id();
    connect(orderItemOption, SIGNAL(costChanged(float)),
            this, SLOT(fireTotalsChanged()));
    m_orderItemOptions.append(orderItemOption);
//    if(!isMoved) {
//        Pos::instance()->appendToHistory("AddOrderItem:" + orderItem->serialize());
//    }

    // TODO: check to see if merely moved
    Pos::instance()->appendToHistory("AddOrderItemOption:" + orderItemOption->serialize());
    orderItemOptionsChanged(orderItemOptions());
    fireTotalsChanged();
}

QQmlListProperty<OrderItemOption> OrderItem::orderItemOptions() {
    return QQmlListProperty<OrderItemOption>(this, m_orderItemOptions);
}

QList<OrderItemOption*> OrderItem::orderItemOptionsList() {
    return m_orderItemOptions;
}

OrderItemOption* OrderItem::getOrderItemOption(quint32 id) {
    for(OrderItemOption* item : m_orderItemOptions) {
        if(item->id() == id){
            return item;
        }
    }
    return nullptr;
}

//void OrderItem::removeOrderItemInventoryItem(quint32 id) {
//    for(int i = 0; i < m_orderItemInventoryItems.length(); i++) {
//        if(m_orderItemInventoryItems[i]->property("id").toUInt() == id) {
//            OrderItemInventoryItem *item = m_orderItemInventoryItems[i];
//            m_orderItemInventoryItems.removeAt(i);
//            disconnect(item, SIGNAL(costChanged(float)),
//                       this, SLOT(fireTotalsChanged()));
//            QStringList historyEntry;
//            historyEntry << "RemoveOrderItemInventoryItem" << item->property("ticketId").toString() << item->property("customerId").toString() << item->property("orderItemId").toString() << item->property("id").toString();
//            Pos::instance()->appendToHistory(serializeList(historyEntry));
//            orderItemInventoryItemsChanged(orderItemInventoryItems());
//            fireTotalsChanged();
//            return;
//        }
//    }
//}









QString OrderItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << QString::number(m_ticketId) << QString::number(m_customerId) << m_name << m_type << m_createdStamp.toString() << QString::number(m_price) << QString::number(m_quantity) << m_note << QString::number(m_deleted) << m_submittedStamp.toString() << QString::number(m_isHiddenFromKitchen) << m_prepType;
    return serializeList(vals);
}

OrderItem* OrderItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toInt();
    quint32 ticketId = split[1].toInt();
    quint32 customerId = split[2].toInt();
    QString name = split[3];
    QString type = split[4];
    QDateTime createdStamp = QDateTime::fromString(split[5]);
    float price = split[6].toFloat();
    float quantity = split[7].toFloat();
    QString note = split[8];
    bool deleted = split[9].toInt();

    QDateTime submittedStamp;
    if(split.length() > 10) {
        submittedStamp = QDateTime::fromString(split[10]);
    }

    bool isHiddenFromKitchen = false;
    if(split.length() > 11) {
        isHiddenFromKitchen = split[11].toInt();
    }

    QString prepType = "";
    if(split.length() > 12) {
        prepType = split[12];
    }

    OrderItem *obj = new OrderItem(parent, id, ticketId, customerId, name, type, createdStamp, price, quantity, note, deleted, submittedStamp, isHiddenFromKitchen, prepType);
    return obj;
}





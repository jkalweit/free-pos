#include "OrderItemOption.h"

#include <QMetaProperty>

OrderItemOption::OrderItemOption(QObject *parent, quint32 ticketId, quint32 customerId, quint32 orderItemId, quint32 id, quint32 optionMenuCategoryId, QString name, QString menuItemName, float cost) :
    SimpleSerializable(parent), m_ticketId(ticketId), m_customerId(customerId), m_orderItemId(orderItemId), m_id(id), m_optionMenuCategoryId(optionMenuCategoryId), m_name(name), m_menuItemName(menuItemName), m_cost(cost)
{
}

QStringList OrderItemOption::updatePrefix() {
    return QStringList() << "UpdateOrderItemOption" << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id);
}

quint32 OrderItemOption::ticketId() {
    return m_ticketId;
}

quint32 OrderItemOption::customerId() {
    return m_customerId;
}

quint32 OrderItemOption::orderItemId() {
    return m_orderItemId;
}

quint32 OrderItemOption::id() {
    return m_id;
}

float OrderItemOption::cost() {
    return m_cost;
}

void OrderItemOption::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void OrderItemOption::setMenuItemName(QString menuItemName) {
    if(m_menuItemName != menuItemName) {
        m_menuItemName = menuItemName;
        logPropertyChanged(m_menuItemName, "menuItemName");
        menuItemNameChanged(m_menuItemName);
    }
}

void OrderItemOption::setCost(float cost) {
    if(m_cost != cost) {
        m_cost = cost;
        logPropertyChanged(m_cost, "cost");
        costChanged(m_cost);
    }
}


QString OrderItemOption::serialize() const {
    QStringList vals;
    vals << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id) << QString::number(m_optionMenuCategoryId) << m_name << m_menuItemName << QString::number(m_cost);
    return serializeList(vals);
}

OrderItemOption* OrderItemOption::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 ticketId = split[0].toInt();
    quint32 customerId = split[1].toInt();
    quint32 orderItemId = split[2].toInt();
    quint32 id = split[3].toInt();
    quint32 optionMenuCategoryId = split[4].toInt();
    QString name = split[5];
    QString menuItemName = split[6];
    float cost = split[7].toFloat();

    OrderItemOption *obj = new OrderItemOption(parent, ticketId, customerId, orderItemId, id, optionMenuCategoryId, name, menuItemName, cost);
    return obj;
}

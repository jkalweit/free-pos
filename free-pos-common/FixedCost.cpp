#include "FixedCost.h"

#include <QMetaProperty>
#include <QDebug>

FixedCost::FixedCost(QObject *parent, quint32 id, QString name, QString type, float cost) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_type(type), m_cost(cost)
{
}

quint32 FixedCost::id() {
    return m_id;
}

QString FixedCost::name() {
    return m_name;
}

QString FixedCost::type() {
    return m_type;
}

float FixedCost::cost() {
    return m_cost;
}


void FixedCost::setName(QString value) {
    if(m_name != value) {
        m_name = value;
        logFixedCostPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void FixedCost::setType(QString value) {
    if(m_type != value) {
        m_type = value;
        logFixedCostPropertyChanged(m_type, "type");
        typeChanged(m_type);
    }
}

void FixedCost::setCost(float value) {
    if(m_cost != value) {
        m_cost = value;
        logFixedCostPropertyChanged(m_cost, "cost");
        costChanged(m_cost);
    }
}



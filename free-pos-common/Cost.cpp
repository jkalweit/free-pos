#include "Cost.h"

#include <QMetaProperty>
#include <QDebug>

Cost::Cost(QObject *parent, quint32 id, QString name, float cost) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_cost(cost)
{
}

QStringList Cost::updatePrefix() {
    return QStringList() << "UpdateCost"; // << QString::number(m_id) << QString::number(m_id);
}

quint32 Cost::id() {
    return m_id;
}

float Cost::cost() {
    return m_cost;
}





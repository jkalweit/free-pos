#include "DailyCost.h"

#include <QMetaProperty>
#include <QDebug>

DailyCost::DailyCost(QObject *parent, quint32 id, QString name) :
    SimpleSerializable(parent), m_id(id), m_name(name)
{
}

quint32 DailyCost::id() {
    return m_id;
}

float DailyCost::cost() {
    // TODO: Implement Read
}




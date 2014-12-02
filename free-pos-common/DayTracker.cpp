#include "DayTracker.h"

#include <QMetaProperty>
#include <QDebug>

DayTracker::DayTracker(QObject *parent, quint32 id, QString name, Reconciliation* lunchRec, Reconciliation* dinnerRec) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_lunchRec(lunchRec), m_dinnerRec(dinnerRec)
{
}

quint32 DayTracker::id() {
    return m_id;
}

QString DayTracker::name() {
    return m_name;
}

float DayTracker::fixedCostTotal() {
    // TODO: Implement Read
}

float DayTracker::cogTotal() {
    // TODO: Implement Read
}

float DayTracker::salesTotal() {
    // TODO: Implement Read
}


void DayTracker::setName(QString value) {
    if(m_name != value) {
        m_name = value;
        nameChanged(m_name);
    }
}


QQmlListProperty<FixedCost> DayTracker::fixedCosts() {
     return QQmlListProperty<FixedCost>(this, m_fixedCosts);
}

QList<FixedCost*> DayTracker::fixedCostsList() {
     return m_fixedCosts;
}

FixedCost* DayTracker::addFixedCost() {
        // TODO: Implement Add
}

void DayTracker::addFixedCost(FixedCost *value) {
     m_fixedCosts.append(value);
     fixedCostsChanged(fixedCosts());
}

FixedCost* DayTracker::getFixedCost(quint32 id) {
    for(FixedCost *value : m_fixedCosts) {
        if(value->property("id").toUInt() == id) {
             return value;
         }
    }
    return nullptr;
}

void DayTracker::removeFixedCost(quint32 id) {
    for(int i = 0; i < m_fixedCosts.length(); i++) {
        if(m_fixedCosts[i]->property("id").toUInt() == id) {
             FixedCost *item = m_fixedCosts[i];
             m_fixedCosts.removeAt(i);
             fixedCostsChanged(fixedCosts());
              return;
         }
    }
}



#include "DayTracker.h"

#include <QMetaProperty>
#include <QDebug>

DayTracker::DayTracker(QObject *parent, quint32 id, QString name, QDate date, Reconciliation* lunchRec, Reconciliation* dinnerRec) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_date(date), m_lunchRec(lunchRec), m_dinnerRec(dinnerRec), m_fixedCostCurrId(0)
{
    m_lunchRec = new Reconciliation(this, 1, m_date, "Lunch", "");
    m_dinnerRec = new Reconciliation(this, 1, m_date, "Dinner", "");

    connect(m_lunchRec, SIGNAL(costChanged(float)),
            this, SLOT(fireCostsChanged()));
    connect(m_dinnerRec, SIGNAL(costChanged(float)),
            this, SLOT(fireCostsChanged()));

    connect(m_lunchRec, SIGNAL(totalChanged(float)),
            this, SLOT(fireSalesChanged()));
    connect(m_dinnerRec, SIGNAL(totalChanged(float)),
            this, SLOT(fireSalesChanged()));
}

QStringList DayTracker::updatePrefix() {
    return QStringList() << "UpdateDayTracker"; // << QString::number(m_id) << QString::number(m_id);
}

quint32 DayTracker::id() {
    return m_id;
}

QString DayTracker::name() {
    return m_name;
}

Reconciliation* DayTracker::lunchRec() {
    return m_lunchRec;
}

Reconciliation* DayTracker::dinnerRec() {
    return m_dinnerRec;
}

float DayTracker::fixedCostTotal() {
    float total = 0;
    for(Cost *cost : m_fixedCosts) {
        total += cost->cost();
    }
    return total;
}

float DayTracker::cogTotal() {
    return m_lunchRec->cog() + m_dinnerRec->cog();
}

float DayTracker::actualTax() {
    return m_lunchRec->actualTax() + m_dinnerRec->actualTax();
}

float DayTracker::laborCostTotal() {
    return m_lunchRec->laborCost() + m_dinnerRec->laborCost();
}

float DayTracker::costTotal() {
    return fixedCostTotal() + cogTotal() + actualTax() + laborCostTotal();
}

void DayTracker::fireCostsChanged() {
    cogTotalChanged(cogTotal());
    laborCostTotalChanged(laborCostTotal());
    costTotalChanged(costTotal());
}

float DayTracker::salesTotal() {    
    return m_lunchRec->total() + m_dinnerRec->total();
}

void DayTracker::fireSalesChanged() {
    salesTotalChanged(salesTotal());
    actualTaxChanged(actualTax());
}

void DayTracker::setName(QString value) {
    if(m_name != value) {
        m_name = value;
        nameChanged(m_name);
    }
}

void DayTracker::addDefaultFixedCosts() {
//    addFixedCost("Mortgage", 92.30);
//    addFixedCost("Property Tax", 31.25);
//    addFixedCost("Other", 66.66);
    addFixedCost("Total", 665.92f);
}


QQmlListProperty<Cost> DayTracker::fixedCosts() {
     return QQmlListProperty<Cost>(this, m_fixedCosts);
}

QList<Cost*> DayTracker::fixedCostsList() {
     return m_fixedCosts;
}

Cost* DayTracker::addFixedCost(QString name, float cost) {
    // TODO: Implement Add
    Cost *obj = new Cost(this, ++m_fixedCostCurrId, name, cost);
    addFixedCost(obj);
    return obj;
}

void DayTracker::addFixedCost(Cost *value) {
    if(value->id() > m_fixedCostCurrId) m_fixedCostCurrId = value->id();
    m_fixedCosts.append(value);
    fixedCostsChanged(fixedCosts());
    costTotalChanged(costTotal());
}

Cost* DayTracker::getFixedCost(quint32 id) {
    for(Cost *value : m_fixedCosts) {
       if(value->property("id").toUInt() == id) {
           return value;
       }
    }
    return nullptr;
}

void DayTracker::removeFixedCost(quint32 id) {
    for(int i = 0; i < m_fixedCosts.length(); i++) {
        if(m_fixedCosts[i]->property("id").toUInt() == id) {
            //Cost *item = m_fixedCosts[i];
            m_fixedCosts.removeAt(i);
            fixedCostsChanged(fixedCosts());
            costTotalChanged(costTotal());
            return;
        }
    }
}



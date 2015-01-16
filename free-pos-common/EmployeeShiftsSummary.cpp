#include "EmployeeShiftsSummary.h"

#include <QMetaProperty>
#include <QDebug>

EmployeeShiftsSummary::EmployeeShiftsSummary(QObject *parent, QString name, float wage) :
    QObject(parent), m_name(name), m_wage(wage), m_shiftCurrId(0)
{
}

QString EmployeeShiftsSummary::name() {
    return m_name;
}

float EmployeeShiftsSummary::wage() {
    return m_wage;
}

float EmployeeShiftsSummary::hours() {
    float total = 0;
    for(EmployeeShift* shift : m_shifts) {
        total += shift->scheduledOrActualHours();
    }
    return total;
}

float EmployeeShiftsSummary::total() {
    return hours() * wage();
}



QQmlListProperty<EmployeeShift> EmployeeShiftsSummary::shifts() {
    return QQmlListProperty<EmployeeShift>(this, m_shifts);
}

QList<EmployeeShift*> EmployeeShiftsSummary::shiftsList() {
    return m_shifts;
}

EmployeeShift* EmployeeShiftsSummary::addShift() {
    // TODO: Implement Add
    EmployeeShift *obj = new EmployeeShift(this, ++m_shiftCurrId);
    addShift(obj);
    return obj;
}

void EmployeeShiftsSummary::addShift(EmployeeShift *value) {
    if(value->id() > m_shiftCurrId) m_shiftCurrId = value->id();
    m_shifts.append(value);
    shiftsChanged(shifts());
}



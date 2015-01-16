#include "WeekTracker.h"

#include <QMetaProperty>
#include <QDebug>

WeekTracker::WeekTracker(QObject *parent, quint32 id, QString name, DayTracker* sunday, DayTracker* monday, DayTracker* tuesday, DayTracker* wednesday, DayTracker* thursday, DayTracker* friday, DayTracker* saturday) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_sunday(sunday), m_monday(monday), m_tuesday(tuesday), m_wednesday(wednesday), m_thursday(thursday), m_friday(friday), m_saturday(saturday)
{
}

void WeekTracker::createDays(QDate startDate) {

    m_sunday = new DayTracker(this, 1, "Sunday", startDate);
    m_monday = new DayTracker(this, 1, "Monday", startDate.addDays(1));
    m_tuesday = new DayTracker(this, 1, "Tuesday", startDate.addDays(2));
    m_wednesday = new DayTracker(this, 1, "Wednesday", startDate.addDays(3));
    m_thursday = new DayTracker(this, 1, "Thursday", startDate.addDays(4));
    m_friday = new DayTracker(this, 1, "Friday", startDate.addDays(5));
    m_saturday = new DayTracker(this, 1, "Saturday", startDate.addDays(6));

    m_wednesday->addDefaultFixedCosts();
    m_thursday->addDefaultFixedCosts();
    m_friday->addDefaultFixedCosts();
    m_saturday->addDefaultFixedCosts();

    m_days.append(m_sunday);
    m_days.append(m_monday);
    m_days.append(m_tuesday);
    m_days.append(m_wednesday);
    m_days.append(m_thursday);
    m_days.append(m_friday);
    m_days.append(m_saturday);

    for(DayTracker *day : m_days) {
        connect(day, SIGNAL(fixedCostTotalChanged(float)),
                this, SLOT(fireFixedCostTotalChanged()));
        connect(day, SIGNAL(cogTotalChanged(float)),
                this, SLOT(fireCogTotalsChanged()));
        connect(day, SIGNAL(salesTotalChanged(float)),
                this, SLOT(fireSalesTotalsChanged()));

        if(day->lunchRec()) {
            connect(day->lunchRec(), SIGNAL(totalChanged(float)),
                    this, SLOT(fireSalesTotalsChanged()));
        }
        if(day->dinnerRec()) {
            connect(day->dinnerRec(), SIGNAL(totalChanged(float)),
                    this, SLOT(fireSalesTotalsChanged()));
        }
    }

}

QStringList WeekTracker::updatePrefix() {
    return QStringList() << "UpdateWeekTracker"; // << QString::number(m_id) << QString::number(m_id);
}

quint32 WeekTracker::id() {
    return m_id;
}

QDate WeekTracker::date() {
    return m_sunday->date();
}

float WeekTracker::fixedCostTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        total += day->fixedCostTotal();
    }
    return total;
}

void WeekTracker::fireFixedCostTotalChanged() {
    fixedCostTotalChanged(fixedCostTotal());
    costTotalChanged(costTotal());
}

float WeekTracker::lunchActualTaxTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->lunchRec()) total += day->lunchRec()->actualTax();
    }
    return total;
}

float WeekTracker::dinnerActualTaxTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->dinnerRec()) total += day->dinnerRec()->actualTax();
    }
    return total;
}

float WeekTracker::lunchCogTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->lunchRec()) total += day->lunchRec()->cog();
    }
    return total;
}

float WeekTracker::dinnerCogTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->dinnerRec()) total += day->dinnerRec()->cog();
    }
    return total;
}

float WeekTracker::cogTotal() {
    return lunchCogTotal() + dinnerCogTotal();
}

float WeekTracker::lunchLaborCostTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->lunchRec()) total += day->lunchRec()->laborCost();
    }
    return total;
}

float WeekTracker::dinnerLaborCostTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->dinnerRec()) total += day->dinnerRec()->laborCost();
    }
    return total;
}

float WeekTracker::laborCostTotal() {
    return lunchLaborCostTotal() + dinnerLaborCostTotal();
}

float WeekTracker::costTotal() {
    return fixedCostTotal() + cogTotal() + laborCostTotal();
}



void WeekTracker::fireCogTotalsChanged() {
    lunchCogTotalChanged(lunchCogTotal());
    dinnerCogTotalChanged(dinnerCogTotal());
    cogTotalChanged(cogTotal());
    costTotalChanged(costTotal());
}

void WeekTracker::fireLaborCostTotalsChanged() {
    lunchLaborCostTotalChanged(lunchLaborCostTotal());
    dinnerLaborCostTotalChanged(dinnerLaborCostTotal());
    laborCostTotalChanged(laborCostTotal());
    costTotalChanged(costTotal());
}


float WeekTracker::lunchSalesTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->lunchRec()) total += day->lunchRec()->total();
    }
    return total;
}

float WeekTracker::dinnerSalesTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        if(day->dinnerRec()) total += day->dinnerRec()->total();
    }
    return total;
}

float WeekTracker::salesTotal() {
    return lunchSalesTotal() + dinnerSalesTotal();
}

void WeekTracker::fireSalesTotalsChanged() {
    lunchActualTaxTotalChanged(lunchActualTaxTotal());
    dinnerActualTaxTotalChanged(dinnerActualTaxTotal());
    lunchSalesTotalChanged(lunchSalesTotal());
    dinnerSalesTotalChanged(dinnerSalesTotal());
    salesTotalChanged(salesTotal());
}



QQmlListProperty<DayTracker> WeekTracker::days() {
    return QQmlListProperty<DayTracker>(this, m_days);
}


bool WeekTracker::containsDate(QDate date) {
    return date >= m_sunday->date() && date <= m_saturday->date();
}


//QQmlListProperty<EmployeeShift> WeekTracker::selectedEmployeeShifts() {
//    qDebug() << "Doing this";
//    return QQmlListProperty<EmployeeShift>(this, getShiftsByEmployee("Jake"));
//}

QList<EmployeeShift*> WeekTracker::getAllEmployeeShifts() {
    QList<EmployeeShift*> shifts;

    for(DayTracker* day : m_days) {
        for(EmployeeShift* shift : day->lunchRec()->shiftsList()) {
            shifts.append(shift);
        }
        for(EmployeeShift* shift : day->dinnerRec()->shiftsList()) {
            shifts.append(shift);
        }
    }

    qDebug() << "   All shifts: " << shifts.count();
    return shifts;
}

QList<EmployeeShift*> WeekTracker::getShiftsByEmployee(QString name) {
    qDebug() << "Getting shifts for " << name;
    QList<EmployeeShift*> allShifts = getAllEmployeeShifts();
    QList<EmployeeShift*> shifts;

    for(EmployeeShift* shift : allShifts) {
        qDebug() << "   Shift: " << shift->name();
        if(shift->name() == name) {
            shifts.append(shift);
        }
    }

    qDebug() << "   Number of shifts: " << shifts.count();
    return shifts;
}

QQmlListProperty<EmployeeShiftsSummary> WeekTracker::employeeShiftsSummaries() {
    QList<EmployeeShiftsSummary*> summaries;
    QList<EmployeeShift*> allShifts = getAllEmployeeShifts();
    EmployeeShiftsSummary *existingSummary;
    for(EmployeeShift* shift : allShifts){
        existingSummary = nullptr;
        qDebug() << "Shift: " << shift->name();
        for(EmployeeShiftsSummary *summary : summaries) {
            qDebug() << "   Checking: " << summary->name();
            if(summary->name() == shift->name()) {
                qDebug() << "       found: " << summary->name();
                existingSummary = summary;
            }
        }
        if(!existingSummary) {            
            existingSummary = new EmployeeShiftsSummary(this, shift->name());
            qDebug() << "   Created new: " << existingSummary->name();
            summaries.append(existingSummary);
        }
        existingSummary->addShift(shift);
    }
    return QQmlListProperty<EmployeeShiftsSummary>(this, summaries);
}

void WeekTracker::fireEmployeeShiftsSummariesChanged() {
    employeeShiftsSummariesChanged(employeeShiftsSummaries());
}

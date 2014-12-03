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

}

QStringList WeekTracker::updatePrefix() {
    return QStringList() << "UpdateWeekTracker"; // << QString::number(m_id) << QString::number(m_id);
}

quint32 WeekTracker::id() {
    return m_id;
}

float WeekTracker::fixedCostTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        total += day->fixedCostTotal();
    }
    return total;
}

float WeekTracker::cogTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        total += day->cogTotal();
    }
    return total;
}

float WeekTracker::salesTotal() {
    float total = 0;
    for(DayTracker *day : m_days) {
        total += day->salesTotal();
    }
    return total;
}


QQmlListProperty<DayTracker> WeekTracker::days() {
    qDebug() << "Days!";
    return QQmlListProperty<DayTracker>(this, m_days);
}




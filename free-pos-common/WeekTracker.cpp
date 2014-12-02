#include "WeekTracker.h"

#include <QMetaProperty>
#include <QDebug>

WeekTracker::WeekTracker(QObject *parent, quint32 id, QString name, DayTracker* sunday, DayTracker* monday, DayTracker* tuesday, DayTracker* wednesday, DayTracker* thursday, DayTracker* friday, DayTracker* saturday) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_sunday(sunday), m_monday(monday), m_tuesday(tuesday), m_wednesday(wednesday), m_thursday(thursday), m_friday(friday), m_saturday(saturday)
{
}

quint32 WeekTracker::id() {
    return m_id;
}

float WeekTracker::fixedCostTotal() {
    // TODO: Implement Read
}

float WeekTracker::cogTotal() {
    // TODO: Implement Read
}

float WeekTracker::salesTotal() {
    // TODO: Implement Read
}





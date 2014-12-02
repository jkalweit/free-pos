#ifndef WEEKTRACKER_H
#define WEEKTRACKER_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "DayTracker.h"

class WeekTracker : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(DayTracker* sunday MEMBER m_sunday NOTIFY sundayChanged)
    Q_PROPERTY(DayTracker* monday MEMBER m_monday NOTIFY mondayChanged)
    Q_PROPERTY(DayTracker* tuesday MEMBER m_tuesday NOTIFY tuesdayChanged)
    Q_PROPERTY(DayTracker* wednesday MEMBER m_wednesday NOTIFY wednesdayChanged)
    Q_PROPERTY(DayTracker* thursday MEMBER m_thursday NOTIFY thursdayChanged)
    Q_PROPERTY(DayTracker* friday MEMBER m_friday NOTIFY fridayChanged)
    Q_PROPERTY(DayTracker* saturday MEMBER m_saturday NOTIFY saturdayChanged)
    Q_PROPERTY(float fixedCostTotal READ fixedCostTotal NOTIFY fixedCostTotalChanged)
    Q_PROPERTY(float cogTotal READ cogTotal NOTIFY cogTotalChanged)
    Q_PROPERTY(float salesTotal READ salesTotal NOTIFY salesTotalChanged)

public:
    explicit WeekTracker(QObject *parent = 0, quint32 id = 0, QString name = "", DayTracker* sunday = nullptr, DayTracker* monday = nullptr, DayTracker* tuesday = nullptr, DayTracker* wednesday = nullptr, DayTracker* thursday = nullptr, DayTracker* friday = nullptr, DayTracker* saturday = nullptr);

    quint32 id();
    float fixedCostTotal();
    float cogTotal();
    float salesTotal();




signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void sundayChanged(DayTracker*);
    void mondayChanged(DayTracker*);
    void tuesdayChanged(DayTracker*);
    void wednesdayChanged(DayTracker*);
    void thursdayChanged(DayTracker*);
    void fridayChanged(DayTracker*);
    void saturdayChanged(DayTracker*);
    void fixedCostTotalChanged(float);
    void cogTotalChanged(float);
    void salesTotalChanged(float);


public slots:

private:
    quint32 m_id;
    QString m_name;
    DayTracker* m_sunday;
    DayTracker* m_monday;
    DayTracker* m_tuesday;
    DayTracker* m_wednesday;
    DayTracker* m_thursday;
    DayTracker* m_friday;
    DayTracker* m_saturday;


};

#endif // WEEKTRACKER_H

#ifndef WEEKTRACKER_H
#define WEEKTRACKER_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "DayTracker.h"

#include "EmployeeShift.h"
#include "EmployeeShiftsSummary.h"

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
    Q_PROPERTY(float lunchActualTaxTotal READ lunchActualTaxTotal NOTIFY lunchActualTaxTotalChanged)
    Q_PROPERTY(float dinnerActualTaxTotal READ dinnerActualTaxTotal NOTIFY dinnerActualTaxTotalChanged)
    Q_PROPERTY(float lunchCogTotal READ lunchCogTotal NOTIFY lunchCogTotalChanged)
    Q_PROPERTY(float dinnerCogTotal READ dinnerCogTotal NOTIFY dinnerCogTotalChanged)
    Q_PROPERTY(float cogTotal READ cogTotal NOTIFY cogTotalChanged)
    Q_PROPERTY(float lunchLaborCostTotal READ lunchLaborCostTotal NOTIFY lunchLaborCostTotalChanged)
    Q_PROPERTY(float dinnerLaborCostTotal READ dinnerLaborCostTotal NOTIFY dinnerLaborCostTotalChanged)
    Q_PROPERTY(float laborCostTotal READ laborCostTotal NOTIFY laborCostTotalChanged)
    Q_PROPERTY(float costTotal READ costTotal NOTIFY costTotalChanged)
    Q_PROPERTY(float lunchSalesTotal READ lunchSalesTotal NOTIFY lunchSalesTotalChanged)
    Q_PROPERTY(float dinnerSalesTotal READ dinnerSalesTotal NOTIFY dinnerSalesTotalChanged)
    Q_PROPERTY(float salesTotal READ salesTotal NOTIFY salesTotalChanged)

    Q_PROPERTY(QQmlListProperty<DayTracker> days READ days NOTIFY daysChanged)

    Q_PROPERTY(QQmlListProperty<EmployeeShiftsSummary> employeeShiftsSummaries READ employeeShiftsSummaries NOTIFY employeeShiftsSummariesChanged)
public:
    explicit WeekTracker(QObject *parent = 0, quint32 id = 0, QString name = "", DayTracker* sunday = nullptr, DayTracker* monday = nullptr, DayTracker* tuesday = nullptr, DayTracker* wednesday = nullptr, DayTracker* thursday = nullptr, DayTracker* friday = nullptr, DayTracker* saturday = nullptr);

    virtual QStringList updatePrefix();

    void createDays(QDate startDate);

    quint32 id();
    QDate date();
    float fixedCostTotal();
    float lunchActualTaxTotal();
    float dinnerActualTaxTotal();
    float lunchCogTotal();
    float dinnerCogTotal();    
    float cogTotal();
    float lunchLaborCostTotal();
    float dinnerLaborCostTotal();
    float laborCostTotal();
    float costTotal();
    float lunchSalesTotal();
    float dinnerSalesTotal();
    float salesTotal();

    QQmlListProperty<DayTracker> days();

    bool containsDate(QDate date);


//    QQmlListProperty<EmployeeShift> selectedEmployeeShifts();
    QList<EmployeeShift*> getAllEmployeeShifts();
    QList<EmployeeShift*> getShiftsByEmployee(QString name);
    QQmlListProperty<EmployeeShiftsSummary> employeeShiftsSummaries();

    Q_INVOKABLE void fireEmployeeShiftsSummariesChanged();

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
    void lunchActualTaxTotalChanged(float);
    void dinnerActualTaxTotalChanged(float);
    void lunchCogTotalChanged(float);
    void dinnerCogTotalChanged(float);
    void cogTotalChanged(float);
    void lunchLaborCostTotalChanged(float);
    void dinnerLaborCostTotalChanged(float);
    void laborCostTotalChanged(float);
    void costTotalChanged(float);
    void lunchSalesTotalChanged(float);
    void dinnerSalesTotalChanged(float);
    void salesTotalChanged(float);

    void daysChanged(QQmlListProperty<DayTracker>);
    void employeeShiftsSummariesChanged(QQmlListProperty<EmployeeShiftsSummary>);

public slots:
    void fireFixedCostTotalChanged();
    void fireCogTotalsChanged();
    void fireLaborCostTotalsChanged();
    void fireSalesTotalsChanged();

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

    QList<DayTracker*> m_days;

};

#endif // WEEKTRACKER_H

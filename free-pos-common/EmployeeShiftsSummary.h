#ifndef EMPLOYEESHIFTSSUMMARY_H
#define EMPLOYEESHIFTSSUMMARY_H

#include <QObject>
#include <QQmlListProperty>
#include "EmployeeShift.h"

class EmployeeShiftsSummary : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name READ name NOTIFY nameChanged)
    Q_PROPERTY(float wage MEMBER m_wage READ wage NOTIFY wageChanged)
    Q_PROPERTY(float hours READ hours NOTIFY hoursChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)

    Q_PROPERTY(QQmlListProperty<EmployeeShift> shifts READ shifts NOTIFY shiftsChanged)
public:
    explicit EmployeeShiftsSummary(QObject *parent = 0, QString name = "", float wage = 0);

    QString name();
    float wage();
    float hours();
    float total();



    QQmlListProperty<EmployeeShift> shifts();
    QList<EmployeeShift*> shiftsList();
    Q_INVOKABLE EmployeeShift* addShift();
    void addShift(EmployeeShift *value);


signals:
    void nameChanged(QString);
    void wageChanged(float);
    void hoursChanged(float);
    void totalChanged(float);

    void shiftsChanged(QQmlListProperty<EmployeeShift>);

public slots:

private:
    QString m_name;
    float m_wage;

    QList<EmployeeShift*> m_shifts;
    quint32 m_shiftCurrId;

};

#endif // EMPLOYEESHIFTSSUMMARY_H

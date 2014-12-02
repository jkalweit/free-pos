#ifndef DAYTRACKER_H
#define DAYTRACKER_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "Reconciliation.h"
#include "FixedCost.h"

class DayTracker : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Reconciliation* lunchRec MEMBER m_lunchRec NOTIFY lunchRecChanged)
    Q_PROPERTY(Reconciliation* dinnerRec MEMBER m_dinnerRec NOTIFY dinnerRecChanged)
    Q_PROPERTY(float fixedCostTotal READ fixedCostTotal NOTIFY fixedCostTotalChanged)
    Q_PROPERTY(float cogTotal READ cogTotal NOTIFY cogTotalChanged)
    Q_PROPERTY(float salesTotal READ salesTotal NOTIFY salesTotalChanged)

    Q_PROPERTY(QQmlListProperty<FixedCost> fixedCosts READ fixedCosts NOTIFY fixedCostsChanged)
public:
    explicit DayTracker(QObject *parent = 0, quint32 id = 0, QString name = "", Reconciliation* lunchRec = nullptr, Reconciliation* dinnerRec = nullptr);

    quint32 id();
    QString name();
    float fixedCostTotal();
    float cogTotal();
    float salesTotal();

    void setName(QString value);


     QQmlListProperty<FixedCost> fixedCosts();
     QList<FixedCost*> fixedCostsList();
     Q_INVOKABLE FixedCost* addFixedCost();
     void addFixedCost(FixedCost *value);
     Q_INVOKABLE FixedCost* getFixedCost(quint32 id);
     Q_INVOKABLE void removeFixedCost(quint32 id);


signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void lunchRecChanged(Reconciliation*);
    void dinnerRecChanged(Reconciliation*);
    void fixedCostTotalChanged(float);
    void cogTotalChanged(float);
    void salesTotalChanged(float);

    void fixedCostsChanged(QQmlListProperty<FixedCost>);

public slots:

private:
    quint32 m_id;
    QString m_name;
    Reconciliation* m_lunchRec;
    Reconciliation* m_dinnerRec;

    QList<FixedCost*> m_fixedCosts;

};

#endif // DAYTRACKER_H

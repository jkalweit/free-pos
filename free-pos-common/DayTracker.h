#ifndef DAYTRACKER_H
#define DAYTRACKER_H

#include <QObject>
#include <QQmlListProperty>
#include <QDate>
#include "SimpleSerializable.h"
#include "Reconciliation.h"
#include "Cost.h"

class DayTracker : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDate date MEMBER m_date NOTIFY dateChanged)
    Q_PROPERTY(Reconciliation* lunchRec MEMBER m_lunchRec READ lunchRec NOTIFY lunchRecChanged)
    Q_PROPERTY(Reconciliation* dinnerRec MEMBER m_dinnerRec READ dinnerRec NOTIFY dinnerRecChanged)
    Q_PROPERTY(float fixedCostTotal READ fixedCostTotal NOTIFY fixedCostTotalChanged)
    Q_PROPERTY(float cogTotal READ cogTotal NOTIFY cogTotalChanged)
    Q_PROPERTY(float costTotal READ costTotal NOTIFY costTotalChanged)
    Q_PROPERTY(float salesTotal READ salesTotal NOTIFY salesTotalChanged)

    Q_PROPERTY(QQmlListProperty<Cost> fixedCosts READ fixedCosts NOTIFY fixedCostsChanged)
public:
    explicit DayTracker(QObject *parent = 0, quint32 id = 0, QString name = "", QDate date = QDate(), Reconciliation* lunchRec = nullptr, Reconciliation* dinnerRec = nullptr);

    virtual QStringList updatePrefix();

    quint32 id();
    QString name();
    Reconciliation* lunchRec();
    Reconciliation* dinnerRec();
    float fixedCostTotal();
    float cogTotal();
    float costTotal();
    float salesTotal();    

    void setName(QString value);


    void addDefaultFixedCosts();


    QQmlListProperty<Cost> fixedCosts();
    QList<Cost*> fixedCostsList();
    Q_INVOKABLE Cost* addFixedCost(QString name, float cost);
    void addFixedCost(Cost *value);
    Q_INVOKABLE Cost* getFixedCost(quint32 id);
    Q_INVOKABLE void removeFixedCost(quint32 id);


signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void dateChanged(QDate);
    void lunchRecChanged(Reconciliation*);
    void dinnerRecChanged(Reconciliation*);
    void fixedCostTotalChanged(float);
    void cogTotalChanged(float);
    void costTotalChanged(float);
    void salesTotalChanged(float);

    void fixedCostsChanged(QQmlListProperty<Cost>);

public slots:
    void fireCostsChanged();
    void fireSalesChanged();

private:
    quint32 m_id;
    QString m_name;
    QDate m_date;
    Reconciliation* m_lunchRec;
    Reconciliation* m_dinnerRec;

    QList<Cost*> m_fixedCosts;
    quint32 m_fixedCostCurrId;

};

#endif // DAYTRACKER_H

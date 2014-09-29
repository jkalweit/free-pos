#ifndef TICKET_H
#define TICKET_H


#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "Customer.h"

class Ticket : public QObject {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
//    Q_PROPERTY(quint32 reconciliationId MEMBER m_reconciliationId NOTIFY reconciliationIdChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString customerNames READ customerNames NOTIFY customerNamesChanged)
    Q_PROPERTY(QString longName READ longName NOTIFY longNameChanged)
    Q_PROPERTY(QQmlListProperty<Customer> customers READ customers NOTIFY customersChanged)

    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit Ticket(QObject *parent = 0, quint32 id = 0, QString name = "");

    QString customerNames();
    QString longName();

    Q_INVOKABLE Customer* addCustomer(QString name);
    void addCustomer(Customer *customer);
    QQmlListProperty<Customer> customers();

    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    QString serialize() const;
    static Ticket* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const Ticket& obj);
    friend QTextStream& operator>>(QTextStream& stream, Ticket& obj);

signals:
    void idChanged(quint32);
//    void reconciliationIdChanged(quint32);
    void nameChanged(QString);
    void customersChanged(QQmlListProperty<Customer>);
    void customerNamesChanged(QString);
    void longNameChanged(QString);

    void foodTotalChanged(float);
    void taxTotalChanged(float);
    void barTotalChanged(float);
    void totalChanged(float);

private:
    quint32 m_id;
//    quint32 m_reconciliationId;
    QString m_name;
    quint32 m_currentCustomerId;
    QList<Customer*> m_customers;

private slots:
    void fireTotalsChanged();
    void fireNamesChanged();
};




#endif // TICKET_H

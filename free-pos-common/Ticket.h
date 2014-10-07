#ifndef TICKET_H
#define TICKET_H

#include <QDateTime>
#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "Customer.h"

class Ticket : public SimpleSerializable {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
//    Q_PROPERTY(quint32 reconciliationId MEMBER m_reconciliationId NOTIFY reconciliationIdChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString customerNames READ customerNames NOTIFY customerNamesChanged)
    Q_PROPERTY(QString longName READ longName NOTIFY longNameChanged)
    Q_PROPERTY(QQmlListProperty<Customer> customers READ customers NOTIFY customersChanged)
    Q_PROPERTY(QDateTime createdStamp MEMBER m_createdStamp NOTIFY createdStampChanged)
    Q_PROPERTY(QDateTime paidStamp MEMBER m_paidStamp NOTIFY paidStampChanged)
    Q_PROPERTY(QString paymentType MEMBER m_paymentType NOTIFY paymentTypeChanged)
    Q_PROPERTY(bool isTogo MEMBER m_isTogo WRITE setIsTogo NOTIFY isTogoChanged)

    Q_PROPERTY(bool isPaid READ isPaid NOTIFY isPaidChanged)
    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit Ticket(QObject *parent = 0, quint32 id = 0, QString name = "", QDateTime createdStamp = QDateTime(),
                    QString paymentType = "", QDateTime paidStamp = QDateTime(), bool isTogo = false);


    void setPaidStamp(QDateTime paidStamp);
    Q_INVOKABLE void cyclePaymentType();    
    void setIsTogo(bool togo);


    Q_INVOKABLE Customer* addCustomer(QString name);
    void addCustomer(Customer *customer);
    QQmlListProperty<Customer> customers();
    Customer* getCustomer(quint32 id);


    QString customerNames();
    QString longName();
    bool isPaid();
    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    Q_INVOKABLE void printKitchen();
    Q_INVOKABLE void printReceipt();

    QString serialize() const;
    static Ticket* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
//    void reconciliationIdChanged(quint32);
    void nameChanged(QString);
    void isTogoChanged(bool);
    void isPaidChanged(bool);
    void createdStampChanged(QDateTime);
    void paymentTypeChanged(QString);
    void paidStampChanged(QDateTime);

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
    QDateTime m_createdStamp;
    QString m_paymentType;
    QDateTime m_paidStamp;
    bool m_isTogo;
    QList<Customer*> m_customers;


private slots:
    void fireTotalsChanged();
    void fireNamesChanged();

    void logPropertyChanged(QVariant value, QString propertyName);
};




#endif // TICKET_H

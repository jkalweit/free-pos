#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QDateTime>
#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class OrderItem : public SimpleSerializable {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(quint32 ticketId MEMBER m_ticketId WRITE setTicketId NOTIFY ticketIdChanged)
    Q_PROPERTY(quint32 customerId MEMBER m_customerId WRITE setCustomerId NOTIFY customerIdChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type NOTIFY typeChanged)
    Q_PROPERTY(QDateTime createdStamp MEMBER m_createdStamp WRITE setCreatedStamp NOTIFY createdStampChanged)
    Q_PROPERTY(float price MEMBER m_price WRITE setPrice NOTIFY priceChanged)
    Q_PROPERTY(float quantity MEMBER m_quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(QString note MEMBER m_note WRITE setNote NOTIFY noteChanged)
    Q_PROPERTY(bool deleted MEMBER m_deleted WRITE setDeleted NOTIFY deletedChanged)
    Q_PROPERTY(QDateTime submittedStamp MEMBER m_submittedStamp WRITE setSubmittedStamp NOTIFY submittedStampChanged)
    Q_PROPERTY(bool isSubmitted READ isSubmitted NOTIFY isSubmittedChanged)

    Q_PROPERTY(float subTotal READ subTotal NOTIFY subTotalChanged)
    Q_PROPERTY(float tax READ tax NOTIFY taxChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit OrderItem(QObject *parent = 0, quint32 id = 0, quint32 ticketId = 0, quint32 customerId = 0, QString name = "", QString type = "", QDateTime createdStamp = QDateTime(), float price = 0, float quantity = 0, QString note = "", bool deleted = false, QDateTime submittedStamp = QDateTime());

    virtual QStringList updatePrefix();

    void setTicketId(quint32 ticketId);
    void setCustomerId(quint32 customerId);
    void setCreatedStamp(QDateTime createdStamp);
    void setPrice(float price);
    void setQuantity(float quantity);
    void setNote(QString note);
    void setDeleted(bool deleted);
    void setSubmittedStamp(QDateTime submittedStamp);

    bool isSubmitted();

    Q_INVOKABLE void cycleSubmittedStamp();

    float subTotal();
    float tax();
    float total();

    QString serialize() const;
    static OrderItem* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void ticketIdChanged(quint32);
    void customerIdChanged(quint32);
    void nameChanged(QString);
    void typeChanged(QString);
    void createdStampChanged(QDateTime);
    void priceChanged(float);
    void quantityChanged(float);
    void noteChanged(QVariant value, QString propertyName = "note");
    void deletedChanged(bool);
    void submittedStampChanged(QDateTime);
    void isSubmittedChanged(bool);

    void subTotalChanged(float);
    void taxChanged(float);
    void totalChanged(float);
private:
    quint32 m_id;
    quint32 m_ticketId;
    quint32 m_customerId;
    QString m_name;
    QString m_type;
    QDateTime m_createdStamp;
    float m_price;
    float m_quantity;
    QString m_note;
    bool m_deleted;
    QDateTime m_submittedStamp;

private slots:
    void fireTotalsChanged();
};

#endif // ORDERITEM_H

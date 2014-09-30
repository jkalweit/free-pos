#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>


class OrderItem : public QObject {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type NOTIFY typeChanged)
    Q_PROPERTY(float price MEMBER m_price NOTIFY priceChanged)
    Q_PROPERTY(float quantity MEMBER m_quantity NOTIFY quantityChanged)
    Q_PROPERTY(QString note MEMBER m_note NOTIFY noteChanged)
    Q_PROPERTY(bool deleted MEMBER m_deleted NOTIFY deletedChanged)

    Q_PROPERTY(float subTotal READ subTotal NOTIFY subTotalChanged)
    Q_PROPERTY(float tax READ tax NOTIFY taxChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit OrderItem(QObject *parent = 0, quint32 id = 0, QString name = "", QString type = "", float price = 0, float quantity = 0, QString note = "", bool deleted = false);

    float subTotal();
    float tax();
    float total();

    QString serialize() const;
    static OrderItem* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const OrderItem& obj);
    friend QTextStream& operator>>(QTextStream& stream, OrderItem& obj);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void typeChanged(QString);
    void priceChanged(float);
    void quantityChanged(float);
    void noteChanged(QString);
    void deletedChanged(bool);

    void subTotalChanged(float);
    void taxChanged(float);
    void totalChanged(float);
private:
    quint32 m_id;
    QString m_name;
    QString m_type;
    float m_price;
    float m_quantity;
    QString m_note;
    bool m_deleted;

private slots:
    void fireTotalsChanged();
};

#endif // ORDERITEM_H

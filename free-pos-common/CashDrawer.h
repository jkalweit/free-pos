#ifndef CASHDRAWER_H
#define CASHDRAWER_H

#include <QDateTime>
#include <QStringList>
#include <QTextStream>
#include <QObject>
#include "SimpleSerializable.h"

class CashDrawer : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QDateTime confirmedStamp MEMBER m_confirmedStamp NOTIFY confirmedStampChanged)

    Q_PROPERTY(quint16 c100s MEMBER m_c100s WRITE setc100s NOTIFY c100sChanged)
    Q_PROPERTY(quint16 c50s MEMBER m_c50s WRITE setc50s NOTIFY c50sChanged)
    Q_PROPERTY(quint16 c20s MEMBER m_c20s WRITE setc20s NOTIFY c20sChanged)
    Q_PROPERTY(quint16 c10s MEMBER m_c10s WRITE setc10s NOTIFY c10sChanged)
    Q_PROPERTY(quint16 c5s MEMBER m_c5s WRITE setc5s NOTIFY c5sChanged)
    Q_PROPERTY(quint16 c1s MEMBER m_c1s WRITE setc1s NOTIFY c1sChanged)
    Q_PROPERTY(float coins MEMBER m_coins WRITE setCoins NOTIFY coinsChanged)
    Q_PROPERTY(float payouts MEMBER m_payouts WRITE setPayouts NOTIFY payoutsChanged)
    Q_PROPERTY(float checks MEMBER m_checks WRITE setChecks NOTIFY checksChanged)
    Q_PROPERTY(float giftCards MEMBER m_giftCards WRITE setGiftCards NOTIFY giftCardsChanged)

    // Calculated
    Q_PROPERTY(float total READ total NOTIFY totalChanged)
public:
    explicit CashDrawer(QObject *parent = 0, quint32 id = 0, QString name = ""
            , quint16 c100s = 0
            , quint16 c50s = 0
            , quint16 c20s = 0
            , quint16 c10s = 0
            , quint16 c5s = 0
            , quint16 c1s = 0
            , float coins = 0
            , float payouts = 0
            , float checks = 0
            , float giftCards = 0);

    virtual QStringList updatePrefix();

    void setc100s(quint16 val);
    void setc50s(quint16 val);
    void setc20s(quint16 val);
    void setc10s(quint16 val);
    void setc5s(quint16 val);
    void setc1s(quint16 val);
    void setCoins(float val);
    void setPayouts(float val);
    void setChecks(float val);
    void setGiftCards(float val);

    float total();

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void confirmedStampChanged(QDateTime);
    void c100sChanged(quint16);
    void c50sChanged(quint16);
    void c20sChanged(quint16);
    void c10sChanged(quint16);
    void c5sChanged(quint16);
    void c1sChanged(quint16);
    void coinsChanged(float);
    void payoutsChanged(float);
    void checksChanged(float);
    void giftCardsChanged(float);

    void totalChanged(float);

public slots:

private:
    quint32 m_id;
    QString m_name;
    QDateTime m_confirmedStamp;

    quint16 m_c100s;
    quint16 m_c50s;
    quint16 m_c20s;
    quint16 m_c10s;
    quint16 m_c5s;
    quint16 m_c1s;
    float m_coins;
    float m_payouts;
    float m_checks;
    float m_giftCards;
};

#endif // CASHDRAWER_H

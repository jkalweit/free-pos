#include "CashDrawer.h"
#include <QDebug>

CashDrawer::CashDrawer(QObject *parent, quint32 id, QString name
                       , quint16 c100s
                       , quint16 c50s
                       , quint16 c20s
                       , quint16 c10s
                       , quint16 c5s
                       , quint16 c1s
                       , float coins
                       , float payouts
                       , float checks
                       , float giftCards) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_confirmedStamp(QDateTime()),
    m_c100s(c100s), m_c50s(c50s), m_c20s(c20s), m_c10s(c10s), m_c5s(c5s), m_c1s(c1s), m_coins(coins),
    m_payouts(payouts), m_checks(checks), m_giftCards(giftCards)
{
}

QStringList CashDrawer::updatePrefix() {
    return QStringList() << "UpdateCashDrawer" << QString::number(m_id);
}

void CashDrawer::setc100s(quint16 val) {
    if(m_c100s != val) {
        m_c100s = val;
        logPropertyChanged(m_c100s, "c100s");
        c100sChanged(m_c100s);
        totalChanged(total());
    }
}
void CashDrawer::setc50s(quint16 val) {
    if(m_c50s != val) {
        m_c50s = val;
        logPropertyChanged(m_c50s, "c50s");
        c50sChanged(m_c50s);
        totalChanged(total());
    }
}
void CashDrawer::setc20s(quint16 val) {
    if(m_c20s != val) {
        m_c20s = val;
        logPropertyChanged(m_c20s, "c20s");
        c20sChanged(m_c20s);
        totalChanged(total());
    }
}
void CashDrawer::setc10s(quint16 val) {
    if(m_c10s != val) {
        m_c10s = val;
        logPropertyChanged(m_c10s, "c10s");
        c10sChanged(m_c10s);
        totalChanged(total());
    }
}
void CashDrawer::setc5s(quint16 val) {
    if(m_c5s != val) {
        m_c5s = val;
        logPropertyChanged(m_c5s, "c5s");
        c5sChanged(m_c5s);
        totalChanged(total());
    }
}
void CashDrawer::setc1s(quint16 val) {
    if(m_c1s != val) {
        m_c1s = val;
        logPropertyChanged(m_c1s, "c1s");
        c1sChanged(m_c1s);
        totalChanged(total());
    }
}
void CashDrawer::setCoins(float val) {
    if(m_coins != val) {
        m_coins = val;
        logPropertyChanged(m_coins, "coins");
        coinsChanged(m_coins);
        totalChanged(total());
    }
}
void CashDrawer::setPayouts(float val) {
    if(m_payouts != val) {
        m_payouts = val;
        logPropertyChanged(m_payouts, "payouts");
        payoutsChanged(m_payouts);
        totalChanged(total());
    }
}
void CashDrawer::setChecks(float val) {
    if(m_checks != val) {
        m_checks = val;
        logPropertyChanged(m_checks, "checks");
        checksChanged(m_checks);
        totalChanged(total());
    }
}
void CashDrawer::setGiftCards(float val) {
    if(m_giftCards != val) {
        m_giftCards = val;
        logPropertyChanged(m_giftCards, "giftCards");
        giftCardsChanged(m_giftCards);
        totalChanged(total());
    }
}
float CashDrawer::total() {
    return m_c100s + m_c50s + m_c20s + m_c10s + m_c5s + m_c1s + m_coins + m_payouts + m_checks + m_giftCards;
}

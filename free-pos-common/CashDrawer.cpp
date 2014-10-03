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
    QObject(parent), m_id(id), m_name(name), m_confirmedStamp(QDateTime()),
    m_c100s(c100s), m_c50s(c50s), m_c20s(c20s), m_c10s(c10s), m_c5s(c5s), m_c1s(c1s), m_coins(coins),
    m_payouts(payouts), m_checks(checks), m_giftCards(giftCards)
{
}

void CashDrawer::setc100s(quint16 val) {
    m_c100s = val;
    c100sChanged(m_c100s);    
    totalChanged(total());
}
void CashDrawer::setc50s(quint16 val) {
    m_c50s = val;
    c50sChanged(m_c50s);
    totalChanged(total());
}
void CashDrawer::setc20s(quint16 val) {
    m_c20s = val;
    c20sChanged(m_c20s);
    totalChanged(total());
}
void CashDrawer::setc10s(quint16 val) {
    m_c10s = val;
    c10sChanged(m_c10s);
    totalChanged(total());
}
void CashDrawer::setc5s(quint16 val) {
    m_c5s = val;
    c5sChanged(m_c5s);
    totalChanged(total());
}
void CashDrawer::setc1s(quint16 val) {
    m_c1s = val;
    c1sChanged(m_c1s);
    totalChanged(total());
}
void CashDrawer::setCoins(float val) {
    m_coins = val;
    coinsChanged(m_coins);
    totalChanged(total());
}
void CashDrawer::setPayouts(float val) {
    m_payouts = val;
    payoutsChanged(m_payouts);
    totalChanged(total());
}
void CashDrawer::setChecks(float val) {
    m_checks = val;
    checksChanged(m_checks);
    totalChanged(total());
}
void CashDrawer::setGiftCards(float val) {
    m_giftCards = val;
    giftCardsChanged(m_giftCards);
    totalChanged(total());
}
float CashDrawer::total() {
    return m_c100s + m_c50s + m_c20s + m_c10s + m_c5s + m_c1s + m_coins + m_payouts + m_checks + m_giftCards;
}

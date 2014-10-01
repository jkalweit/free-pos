#include "CashDrawer.h"

CashDrawer::CashDrawer(QObject *parent, quint32 id, QString name) :
    QObject(parent), m_id(id), m_name(name), m_confirmedStamp(QDateTime()), m_c100s(0), m_c50s(0), m_c20s(0), m_c10s(0), m_c5s(0), m_c1s(0), m_coins(0)
{
}

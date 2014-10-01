#include "Reconciliation.h"

#include <QMetaProperty>
#include <QDebug>


Reconciliation::Reconciliation(QObject *parent, quint32 id, QString name, CashDrawer *begginningDrawer, CashDrawer *endingDrawer) :
    QObject(parent), m_id(id), m_name(name), m_beginningDrawer(begginningDrawer), m_endingDrawer(endingDrawer),
    m_currentTicketId(0), m_selectedTicket(nullptr)
{
    if(m_beginningDrawer == nullptr)
        m_beginningDrawer = new CashDrawer(this);
    if(m_endingDrawer == nullptr)
        m_endingDrawer = new CashDrawer(this);
}

CashDrawer* Reconciliation::beginningDrawer() {
    return m_beginningDrawer;
}

CashDrawer* Reconciliation::endingDrawer() {
    return m_endingDrawer;
}

Ticket* Reconciliation::addTicket(QString name) {
    Ticket *ticket = new Ticket(this, ++m_currentTicketId, name);
    addTicket(ticket);
    return ticket;
}

void Reconciliation::addTicket(Ticket *ticket) {
    connect(ticket, SIGNAL(foodTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(taxTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(barTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));

    m_tickets.append(ticket);
    ticketsChanged(tickets());
}

void Reconciliation::setSelectedTicket(Ticket *ticket) {
    if(m_selectedTicket != ticket) {
        m_selectedTicket = ticket;
        selectedTicketChanged(m_selectedTicket);
    }
}

Ticket* Reconciliation::selectedTicket() {
    return m_selectedTicket;
}

QQmlListProperty<Ticket> Reconciliation::tickets() {
    return QQmlListProperty<Ticket>(this, m_tickets);
}


float Reconciliation::foodTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->foodTotal();
    }
    return sum;
}

float Reconciliation::taxTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->taxTotal();
    }
    return sum;
}

float Reconciliation::barTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->barTotal();
    }
    return sum;
}

float Reconciliation::total() {
    return foodTotal() + taxTotal() + barTotal();
}

void Reconciliation::fireTotalsChanged() {
    foodTotalChanged(foodTotal());
    taxTotalChanged(taxTotal());
    barTotalChanged(barTotal());
    totalChanged(total());
}

QString Reconciliation::serialize() const {
    return QString::number(m_id) + ":" + m_name;
}

Reconciliation* Reconciliation::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    QString name = split[2];

    Reconciliation *obj = new Reconciliation(parent, id, name);
    qDebug() << "    deserialized: " << obj->serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const Reconciliation& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, Reconciliation& obj) {

    QString line = stream.readAll();
    qDebug() << "Got line: " << line;
    if(line.length() <= 1){
        qDebug() << "Empty line.";
        return stream;
    }
    Reconciliation* obj2 = Reconciliation::deserialize(line);
    obj.m_id = obj2->m_id;
    obj.m_name = obj2->m_name;

    return stream;
}

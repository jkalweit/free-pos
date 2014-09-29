#include "Reconciliation.h"

#include <QMetaProperty>
#include <QDebug>


Reconciliation::Reconciliation(QObject *parent, quint32 id, QString name) :
    QObject(parent), m_id(id), m_name(name), m_currentTicketId(0), m_selectedTicket(nullptr)
{
}

Ticket* Reconciliation::addTicket(QString name) {
    Ticket *ticket = new Ticket(this, ++m_currentTicketId, name);
    addTicket(ticket);
    return ticket;
}

void Reconciliation::addTicket(Ticket *ticket) {
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

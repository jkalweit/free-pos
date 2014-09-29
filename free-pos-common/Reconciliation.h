#ifndef RECONCILIATION_H
#define RECONCILIATION_H

#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "Ticket.h"

class Reconciliation : public QObject {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(Ticket *selectedTicket READ selectedTicket WRITE setSelectedTicket NOTIFY selectedTicketChanged)
    Q_PROPERTY(QQmlListProperty<Ticket> tickets READ tickets NOTIFY ticketsChanged)    
public:
    explicit Reconciliation(QObject *parent = 0, quint32 id = 0, QString name = "");

    QQmlListProperty<Ticket> tickets();
    Q_INVOKABLE Ticket* addTicket(QString name);
    void addTicket(Ticket *ticket);

    void setSelectedTicket(Ticket *ticket);
    Ticket* selectedTicket();

    QString serialize() const;
    static Reconciliation* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const Reconciliation& obj);
    friend QTextStream& operator>>(QTextStream& stream, Reconciliation& obj);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void ticketsChanged(QQmlListProperty<Ticket>);
    void selectedTicketChanged(Ticket*);

private:
    quint32 m_id;
    QString m_name;

    quint32 m_currentTicketId;
    QList<Ticket*> m_tickets;
    Ticket* m_selectedTicket;
};



#endif // RECONCILIATION_H

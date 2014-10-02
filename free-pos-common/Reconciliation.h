#ifndef RECONCILIATION_H
#define RECONCILIATION_H

#include <QDateTime>
#include <QTextStream>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "Ticket.h"
#include "CashDrawer.h"

class Reconciliation : public QObject {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString note MEMBER m_note NOTIFY noteChanged)
    Q_PROPERTY(QDateTime openedStamp MEMBER m_openedStamp NOTIFY openedStampChanged)
    Q_PROPERTY(QDateTime closedStamp MEMBER m_closedStamp NOTIFY closedStampChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(Ticket *selectedTicket READ selectedTicket WRITE setSelectedTicket NOTIFY selectedTicketChanged)
    Q_PROPERTY(QQmlListProperty<Ticket> tickets READ tickets NOTIFY ticketsChanged)    

    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)

    Q_PROPERTY(CashDrawer *beginningDrawer READ beginningDrawer NOTIFY beginningDrawerChanged)
    Q_PROPERTY(CashDrawer *endingDrawer READ endingDrawer NOTIFY endingDrawerChanged)
public:
    explicit Reconciliation(QObject *parent = 0, quint32 id = 0, QString name = "", QString note = "",
                            QDateTime openedStamp = QDateTime(), QDateTime closedStamp = QDateTime(),
                            CashDrawer *begginningDrawer = nullptr, CashDrawer *endingDrawer = nullptr);

    QQmlListProperty<Ticket> tickets();
    Q_INVOKABLE Ticket* addTicket(QString name);
    void addTicket(Ticket *ticket);

    void setSelectedTicket(Ticket *ticket);
    Ticket* selectedTicket();

    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    CashDrawer* beginningDrawer();
    CashDrawer* endingDrawer();

    Q_INVOKABLE bool hasOpenTickets();
    Q_INVOKABLE void closeRec();
    Q_INVOKABLE bool isOpen();

    QString serialize() const;
    static Reconciliation* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const Reconciliation& obj);
    friend QTextStream& operator>>(QTextStream& stream, Reconciliation& obj);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void noteChanged(QString);
    void openedStampChanged(QDateTime);
    void closedStampChanged(QDateTime);
    void isOpenChanged(bool);
    void ticketsChanged(QQmlListProperty<Ticket>);
    void selectedTicketChanged(Ticket*);

    void foodTotalChanged(float);
    void taxTotalChanged(float);
    void barTotalChanged(float);
    void totalChanged(float);

    void beginningDrawerChanged(CashDrawer*);
    void endingDrawerChanged(CashDrawer*);

private:
    quint32 m_id;
    QString m_name;
    QString m_note;
    QDateTime m_openedStamp;
    QDateTime m_closedStamp;

    CashDrawer *m_beginningDrawer;
    CashDrawer *m_endingDrawer;

    quint32 m_currentTicketId;
    QList<Ticket*> m_tickets;
    Ticket* m_selectedTicket;    

private slots:
    void fireTotalsChanged();
};



#endif // RECONCILIATION_H

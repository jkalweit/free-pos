#include "Reconciliation.h"

#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"

Reconciliation::Reconciliation(QObject *parent, quint32 id, QString name, QString note,
                               QDateTime openedStamp, QDateTime closedStamp,
                               CashDrawer *begginningDrawer, CashDrawer *endingDrawer,
                               float creditCardTotalActual, float creditCardTotalTips) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_note(note),
    m_openedStamp(openedStamp), m_closedStamp(closedStamp),
    m_beginningDrawer(begginningDrawer), m_endingDrawer(endingDrawer),
    m_currentTicketId(0), m_selectedTicket(nullptr), m_creditCardTotalActual(creditCardTotalActual), m_creditCardTotalTips(creditCardTotalTips)
{
    if(m_beginningDrawer == nullptr)
        m_beginningDrawer = new CashDrawer(this, 1);
    if(m_endingDrawer == nullptr)
        m_endingDrawer = new CashDrawer(this, 2);


    connect(m_beginningDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));
    connect(m_endingDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));
}

QStringList Reconciliation::updatePrefix() {
    return QStringList() << "UpdateReconciliation" << QString::number(m_id);
}

CashDrawer* Reconciliation::beginningDrawer() {
    return m_beginningDrawer;
}

CashDrawer* Reconciliation::endingDrawer() {
    return m_endingDrawer;
}

Ticket* Reconciliation::addTicket(QString name) {
    Ticket *ticket = new Ticket(this, ++m_currentTicketId, name, QDateTime::currentDateTime());
    addTicket(ticket);
    return ticket;
}

void Reconciliation::addTicket(Ticket *ticket) {
    if(ticket->property("id").toUInt() > m_currentTicketId) m_currentTicketId = ticket->property("id").toUInt();

    connect(ticket, SIGNAL(foodTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(taxTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(barTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));

    connect(ticket, SIGNAL(paymentTypeChanged(QString)),
            this, SLOT(firePaymentTotalsChanged()));

    m_tickets.append(ticket);
    Pos *pos = Pos::instance();
    pos->appendToHistory("AddTicket:" + ticket->serialize());
    ticketsChanged(tickets());
}

void Reconciliation::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void Reconciliation::setNote(QString note) {
    if(m_note != note.trimmed()) {
        m_note = note.trimmed();
        logPropertyChanged(m_note, "note");
        noteChanged(m_note);
    }
}

Ticket* Reconciliation::getTicket(quint32 id) {
    for(Ticket *ticket : m_tickets) {
        if(ticket->property("id").toUInt() == id)
            return ticket;
    }
    return nullptr;
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

QString Reconciliation::fileName() {
    return m_openedStamp.toString("yyyy-MM-dd") + "_" + m_name + ".txt";
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

void Reconciliation::fireActualTakeTotalsChanged() {
    cashTotalActualChanged(cashTotalActual());    
    creditCardTotalActualChanged(m_creditCardTotalActual);
    creditCardTotalTipsChanged(m_creditCardTotalTips);
    takeTotalActualChanged(takeTotalActual());
    discrepancyActualChanged(discrepancyActual());
}

float Reconciliation::creditCardTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        if(c->property("paymentType").toString() == "Credit Card")
            sum += c->total();
    }
    return sum;
}

void Reconciliation::setCreditCardTotalActual(float val) {
    m_creditCardTotalActual = val;
    logPropertyChanged(m_creditCardTotalActual, "creditCardTotalActual");
    creditCardTotalActualChanged(m_creditCardTotalActual);
    fireActualTakeTotalsChanged();
}

void Reconciliation::setCreditCardTotalTips(float val) {
    m_creditCardTotalTips = val;
    logPropertyChanged(m_creditCardTotalTips, "creditCardTotalTips");
    creditCardTotalTipsChanged(m_creditCardTotalTips);
    fireActualTakeTotalsChanged();
}

float Reconciliation::cashTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        if(c->property("paymentType").toString() == "Cash")
            sum += c->total();
    }
    return sum;
}

float Reconciliation::cashTotalActual() {
    return m_endingDrawer->total() - m_beginningDrawer->total();
}

float Reconciliation::takeTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->total();
    }
    return sum;
}

float Reconciliation::takeTotalActual() {
    return cashTotalActual() + m_creditCardTotalActual + m_creditCardTotalTips;
}

float Reconciliation::discrepancy() {
    return takeTotal() - total();
}

float Reconciliation::discrepancyActual() {
    return takeTotalActual() - total();
}

void Reconciliation::firePaymentTotalsChanged() {
    creditCardTotalChanged(creditCardTotal());
    cashTotalChanged(cashTotal());
    takeTotalChanged(takeTotal());
    discrepancyChanged(discrepancy());
}

bool Reconciliation::hasOpenTickets() {
    for(Ticket *t : m_tickets) {
        if(!t->isPaid()) {
            return true;
        }
    }
    return false;
}

bool Reconciliation::closeRec() {
    if(!isOpen()) {
        qDebug() << "Rec is already closed.";
        return false;
    }

    if(hasOpenTickets()) {
        qDebug() << "Rec has open customers.";
        return false;
    }

    m_closedStamp = QDateTime::currentDateTime();    
    logPropertyChanged(m_closedStamp, "closedStamp");
    if(!Pos::instance()->closeCurrentRec()) {
        m_closedStamp = QDateTime();
        logPropertyChanged(m_closedStamp, "closedStamp");
    } else {
        qDebug() << "Closed rec: " << m_closedStamp.toString("MM/dd/yyyy hh:mmAP");        
    }

    closedStampChanged(m_closedStamp);
    isOpenChanged(isOpen());

    return !isOpen();
}

bool Reconciliation::isOpen() {
    return m_closedStamp.isNull();
}



QString Reconciliation::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << m_note << m_openedStamp.toString();
    return serializeList(vals);
}

Reconciliation* Reconciliation::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toInt();
    QString name = split[1];
    QString note = split[2];
    QDateTime opened = QDateTime::fromString(split[3]);

    Reconciliation *obj = new Reconciliation(parent, id, name, note, opened);
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

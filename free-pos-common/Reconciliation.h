#ifndef RECONCILIATION_H
#define RECONCILIATION_H

#include <QDateTime>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "Ticket.h"
#include "CashDrawer.h"
#include "EmployeeShift.h"

class Reconciliation : public SimpleSerializable {

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QDate date MEMBER m_date NOTIFY dateChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)    
    Q_PROPERTY(QString note MEMBER m_note WRITE setNote NOTIFY noteChanged)
    Q_PROPERTY(QDateTime openedStamp MEMBER m_openedStamp NOTIFY openedStampChanged)
    Q_PROPERTY(QDateTime closedStamp MEMBER m_closedStamp NOTIFY closedStampChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(Ticket *selectedTicket READ selectedTicket WRITE setSelectedTicket NOTIFY selectedTicketChanged)
    Q_PROPERTY(QQmlListProperty<Ticket> tickets READ tickets NOTIFY ticketsChanged)    

    Q_PROPERTY(float foodTotal READ foodTotal NOTIFY foodTotalChanged)
    Q_PROPERTY(float taxTotal READ taxTotal NOTIFY taxTotalChanged)
    Q_PROPERTY(float barTotal READ barTotal NOTIFY barTotalChanged)
    Q_PROPERTY(float total READ total NOTIFY totalChanged)

    Q_PROPERTY(float creditCardTotal READ creditCardTotal NOTIFY creditCardTotalChanged)
    Q_PROPERTY(float creditCardTotalActual MEMBER m_creditCardTotalActual WRITE setCreditCardTotalActual NOTIFY creditCardTotalActualChanged)
    Q_PROPERTY(float creditCardTotalTips MEMBER m_creditCardTotalTips WRITE setCreditCardTotalTips NOTIFY creditCardTotalTipsChanged)
    Q_PROPERTY(float cashTotal READ cashTotal NOTIFY cashTotalChanged)
    Q_PROPERTY(float cashTotalActual READ cashTotalActual NOTIFY cashTotalActualChanged)
    Q_PROPERTY(float takeTotal READ takeTotal NOTIFY takeTotalChanged)
    Q_PROPERTY(float takeTotalActual READ takeTotalActual NOTIFY takeTotalActualChanged)
    Q_PROPERTY(float discrepancy READ discrepancy NOTIFY discrepancyChanged)
    Q_PROPERTY(float discrepancyActual READ discrepancyActual NOTIFY discrepancyActualChanged)

    Q_PROPERTY(CashDrawer *beginningDrawer READ beginningDrawer NOTIFY beginningDrawerChanged)
    Q_PROPERTY(CashDrawer *endingDrawer READ endingDrawer NOTIFY endingDrawerChanged)

    Q_PROPERTY(float cog READ cog NOTIFY cogChanged)
    Q_PROPERTY(float laborHours READ laborHours NOTIFY laborHoursChanged)
    Q_PROPERTY(float laborCost READ laborCost NOTIFY laborCostChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
    Q_PROPERTY(float margin READ margin NOTIFY marginChanged)

    Q_PROPERTY(QQmlListProperty<EmployeeShift> shifts READ shifts NOTIFY shiftsChanged)

public:
    explicit Reconciliation(QObject *parent = 0, quint32 id = 0, QDate date = QDate(), QString name = "", QString note = "",
                            QDateTime openedStamp = QDateTime(), QDateTime closedStamp = QDateTime(),
                            CashDrawer *begginningDrawer = nullptr, CashDrawer *endingDrawer = nullptr,
                            float creditCardTotalActual = 0, float creditCardTotalTips = 0);

    virtual QStringList updatePrefix();
    QString filename();
    void readHistory();
    void appendToHistory(QString item);

    void setName(QString name);
    void setNote(QString note);

    QQmlListProperty<Ticket> tickets();
    Q_INVOKABLE Ticket* addTicket(QString name);
    void addTicket(Ticket *ticket);

    void setSelectedTicket(Ticket *ticket);
    Ticket* selectedTicket();
    Q_INVOKABLE Ticket* getNextTicket(QString nameFilter, bool showIsPaid);
    Q_INVOKABLE Ticket* getPreviousTicket(QString nameFilter, bool showIsPaid);

    Q_INVOKABLE void moveOrderItem(OrderItem* orderItem, quint32 toTicketId, quint32 toCustomerId);

    QString fileName();

    float foodTotal();
    float taxTotal();
    float barTotal();
    float total();

    float creditCardTotal();
    void setCreditCardTotalActual(float);
    void setCreditCardTotalTips(float);
    float cashTotal();
    float cashTotalActual();
    float takeTotal();
    float takeTotalActual();

    float discrepancy();
    float discrepancyActual();

    CashDrawer* beginningDrawer();
    CashDrawer* endingDrawer();

    Q_INVOKABLE bool hasOpenTickets();    
    Q_INVOKABLE bool closeRec();
    Q_INVOKABLE bool isOpen();

    float cog();
    float laborHours();
    float laborCost();
    float cost();
    float margin();

    Ticket* getTicket(quint32 id);

    Q_INVOKABLE void print();

    QQmlListProperty<EmployeeShift> shifts();
    QList<EmployeeShift*> shiftsList();
    Q_INVOKABLE EmployeeShift* addShift(QString name, QString note, float wage, quint8 scheduledStartHour, quint8 scheduledStartMinute, bool scheduledStartAM, quint8 scheduledEndHour, quint8 scheduledEndMinute, bool scheduledEndAM);
    void addShift(EmployeeShift *value);
    Q_INVOKABLE EmployeeShift* getShift(quint32 id);
    Q_INVOKABLE void removeShift(quint32 id);

    QString serialize() const;
    static Reconciliation* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void dateChanged(QDate);
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

    void creditCardTotalChanged(float);
    void creditCardTotalActualChanged(float);
    void creditCardTotalTipsChanged(float);
    void cashTotalChanged(float);
    void cashTotalActualChanged(float);
    void takeTotalChanged(float);
    void takeTotalActualChanged(float);

    void discrepancyChanged(float);
    void discrepancyActualChanged(float);

    void beginningDrawerChanged(CashDrawer*);
    void endingDrawerChanged(CashDrawer*);

    void cogChanged(float);
    void laborHoursChanged(float);
    void laborCostChanged(float);
    void costChanged(float);
    void marginChanged(float);

    void shiftsChanged(QQmlListProperty<EmployeeShift>);

private:
    quint32 m_id;
    QDate m_date;
    QString m_name;    
    QString m_note;
    QDateTime m_openedStamp;
    QDateTime m_closedStamp;    

    CashDrawer *m_beginningDrawer;
    CashDrawer *m_endingDrawer;

    quint32 m_currentTicketId;
    QList<Ticket*> m_tickets;
    Ticket* m_selectedTicket;

    float m_creditCardTotalActual;
    float m_creditCardTotalTips;

    bool m_isHistoryDisabled;

    QList<EmployeeShift*> m_shifts;
    quint32 m_shiftCurrId;

private slots:
    void fireCogChanged();
    void fireLaborCostChanged();
    void fireTotalsChanged();
    void firePaymentTotalsChanged();
    void fireActualTakeTotalsChanged();    
};



#endif // RECONCILIATION_H

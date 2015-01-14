#ifndef POS_H
#define POS_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "Menu.h"
#include "Reconciliation.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "WeekTracker.h"

class Pos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Menu> menus READ menus NOTIFY menusChanged)
    Q_PROPERTY(Menu* selectedMenu MEMBER m_selectedMenu READ selectedMenu NOTIFY selectedMenuChanged)
    Q_PROPERTY(QQmlListProperty<Reconciliation> reconciliations READ reconciliations NOTIFY reconciliationsChanged)
    Q_PROPERTY(Reconciliation* selectedRec MEMBER m_selectedRec READ selectedRec NOTIFY selectedRecChanged)
    Q_PROPERTY(Inventory* selectedInventory MEMBER m_selectedInventory READ selectedInventory NOTIFY selectedInventoryChanged)
    Q_PROPERTY(QQmlListProperty<WeekTracker> weeks READ weeks NOTIFY weeksChanged)
    Q_PROPERTY(WeekTracker* selectedWeek MEMBER m_selectedWeek NOTIFY selectedWeekChanged)
public:    

    static Pos *instance();

    explicit Pos(QObject *parent = 0);

    void readHistory(QString filename);
    void readMenuHistory(QString filename = "currMenu.txt");

    QQmlListProperty<Menu> menus();
    void addMenu(Menu *menu);

    QQmlListProperty<Reconciliation> reconciliations();
    Q_INVOKABLE void unselectRec();
    Reconciliation* selectedRec();
    Menu* selectedMenu();
    Inventory* selectedInventory();
    void addReconciliation(Reconciliation *rec);
    void appendToHistory(QString item);
    void appendToMenuHistory(QString item);
    void appendToInventoryHistory(QString item);
    void appendToTrackerHistory(QString item);
    void appendToFixedCostHistory(QString item);
    void addTestData();

    Q_INVOKABLE WeekTracker* previousWeek();
    Q_INVOKABLE WeekTracker* nextWeek();
    QQmlListProperty<WeekTracker> weeks();
    QList<WeekTracker*> weeksList();
    Q_INVOKABLE WeekTracker* addWeek(QDate startDate);
//    void addWeek(WeekTracker *value);
    Q_INVOKABLE WeekTracker* getWeek(QDate date);
//    Q_INVOKABLE void removeWeek(quint32 id);

signals:
    void menusChanged(QQmlListProperty<Menu>);
    void selectedMenuChanged(Menu*);
    void reconciliationsChanged(QQmlListProperty<Reconciliation>);
    void selectedRecChanged(Reconciliation*);
    void selectedInventoryChanged(Inventory*);
    void selectedWeekChanged(WeekTracker*);
    void weeksChanged(QQmlListProperty<WeekTracker>);

public slots:

private:
    static Pos *s_instance;
    QList<QString> m_history;
    bool m_isHistoryDisabled;
    QList<Menu*> m_menus;
    Menu* m_selectedMenu;
    QList<Reconciliation*> m_reconciliations;
    Reconciliation *m_selectedRec;
    Inventory *m_selectedInventory;

    WeekTracker *m_selectedWeek;
    QList<WeekTracker*> m_weeks;
    //quint32 m_weekCurrId;

    void appendToFile(QString item, QString filename);
};

#endif // POS_H

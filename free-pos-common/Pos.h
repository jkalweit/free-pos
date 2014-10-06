#ifndef POS_H
#define POS_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "Menu.h"
#include "Reconciliation.h"

class Pos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Menu> menus READ menus NOTIFY menusChanged)
    Q_PROPERTY(Menu* selectedMenu MEMBER m_selectedMenu NOTIFY selectedMenuChanged)
    Q_PROPERTY(QQmlListProperty<Reconciliation> reconciliations READ reconciliations NOTIFY reconciliationsChanged)
    Q_PROPERTY(Reconciliation* selectedRec MEMBER m_selectedRec NOTIFY selectedRecChanged)    

public:    

    static Pos *instance();

    explicit Pos(QObject *parent = 0);

    void readHistory();

    QQmlListProperty<Menu> menus();
    void addMenu(Menu *menu);

    QQmlListProperty<Reconciliation> reconciliations();
    Q_INVOKABLE Reconciliation* openNewRec();
    void addReconciliation(Reconciliation *rec);
    void appendToHistory(QString item);
    void addTestData();

signals:
    void menusChanged(QQmlListProperty<Menu>);
    void selectedMenuChanged(Menu*);
    void reconciliationsChanged(QQmlListProperty<Reconciliation>);
    void selectedRecChanged(Reconciliation*);

public slots:

private:    
    static Pos* s_instance;
    QList<QString> m_history;
    bool m_isHistoryDisabled;
    QList<Menu*> m_menus;
    Menu* m_selectedMenu;
    QList<Reconciliation*> m_reconciliations;
    Reconciliation* m_selectedRec;

};

#endif // POS_H

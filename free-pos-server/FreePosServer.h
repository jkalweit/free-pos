#ifndef FREEPOSSERVER_H
#define FREEPOSSERVER_H

#include <QObject>
#include <QSqlDatabase>
#include "SimpleServer.h"
#include "FreePosCommand.h"
#include "Menu.h"
#include "Reconciliation.h"

class FreePosServer : public SimpleServer
{
    Q_OBJECT
    //Q_PROPERTY(Reconciliation currentRec MEMBER m_currentRec NOTIFY currentRecChanged)
public:
    //~FreePosServer();

    explicit FreePosServer(QObject *parent = 0);
//    Q_INVOKABLE void openDb(QString dbname = "");
//    Q_INVOKABLE void createDb();    
    Q_INVOKABLE void setCurrentMenu(Menu* menu);
    Q_INVOKABLE Menu* getCurrentMenu();
    Q_INVOKABLE void setCurrentRec(Reconciliation* rec);
    Q_INVOKABLE Reconciliation* getCurrentRec();
    Q_INVOKABLE void addTestData();
//    Q_INVOKABLE MenuCategory* getMenuCategory(quint32 id);

signals:
    void currentMenuChanged(Menu*);
    void currentRecChanged(Reconciliation*);    

public slots:

protected:
    void handleMessage(QString msg, std::function<void (QString)> reply);

private:
    Menu *m_currentMenu;
    Reconciliation *m_currentRec;

//    QSqlDatabase m_db;
//    int execInsert(QString sql);
//    bool execQuery(QString sql);

};

#endif // FREEPOSSERVER_H

#ifndef FREEPOSSERVER_H
#define FREEPOSSERVER_H

#include <QObject>
#include <QSqlDatabase>
#include "SimpleServer.h"
#include "FreePosCommand.h"
#include "Pos.h"
#include "Menu.h"
#include "Reconciliation.h"

class FreePosServer : public SimpleServer
{
    Q_OBJECT
public:
    //~FreePosServer();

    explicit FreePosServer(QObject *parent = 0);
//    Q_INVOKABLE void openDb(QString dbname = "");
//    Q_INVOKABLE void createDb();    

signals:

public slots:

protected:
    void handleMessage(QString msg, std::function<void (QString)> reply);

private:
    Pos* m_pos;

//    QSqlDatabase m_db;
//    int execInsert(QString sql);
//    bool execQuery(QString sql);

};

#endif // FREEPOSSERVER_H

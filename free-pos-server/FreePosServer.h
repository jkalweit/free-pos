#ifndef FREEPOSSERVER_H
#define FREEPOSSERVER_H

#include <QObject>
#include <QSqlDatabase>
#include "SimpleServer.h"
#include "MenuCategory.h"

class FreePosServer : public SimpleServer
{
    Q_OBJECT
public:
    ~FreePosServer();

    explicit FreePosServer(QObject *parent = 0);
    Q_INVOKABLE void openDb(QString dbname = "");
    Q_INVOKABLE void createDb();
    Q_INVOKABLE void addTestData();

    Q_INVOKABLE void addMenuCategory(QString name);
    Q_INVOKABLE void addMenuItem(quint32 menucategory, QString name);

    Q_INVOKABLE MenuCategory* getMenuCategory(quint32 id);

signals:

public slots:

protected:
    void handleMessage(QString msg, std::function<void (QString)> reply);

private:
    QSqlDatabase m_db;
    bool execQuery(QString sql);
};

#endif // FREEPOSSERVER_H

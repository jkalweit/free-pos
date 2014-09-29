#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "FreePosServer.h"
#include "Menu.h"
#include "MenuCategory.h"
#include "MenuItem.h"
#include "Reconciliation.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Menu>("FreePos", 1, 0, "Menu");
    qmlRegisterType<MenuCategory>("FreePos", 1, 0, "MenuCategory");
    qmlRegisterType<MenuItem>("FreePos", 1, 0, "MenuItem");
    qmlRegisterType<Reconciliation>("FreePos", 1, 0, "Reconciliation");
    qmlRegisterType<Ticket>("FreePos", 1, 0, "Ticket");
    qmlRegisterType<Customer>("FreePos", 1, 0, "Customer");
    qmlRegisterType<OrderItem>("FreePos", 1, 0, "OrderItem");

    FreePosServer server;
    Menu menu(&server);
    server.setCurrentMenu(&menu);
    Reconciliation rec(&server, 1, "Test Rec2");
    server.setCurrentRec(&rec);
    server.addTestData();

    QQmlApplicationEngine engine;    
    engine.rootContext()->setContextProperty("server", (QObject*)&server);
    engine.rootContext()->setContextProperty("rec", (QObject*)&rec);
    engine.rootContext()->setContextProperty("menu", (QObject*)&menu);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    server.openDb();
//    server.createDb();


    if(server.listen(QHostAddress("127.0.0.1"), 1337)) {
    //if(server.listen(QHostAddress("192.168.10.73"), 1337)) {
        qDebug() << "Listening...";
    } else {
        qDebug() << "Failed to listen on port.";
    }


    return app.exec();
}

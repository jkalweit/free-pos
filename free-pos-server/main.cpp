#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDateTime>
#include "FreePosServer.h"
#include "Menu.h"
#include "MenuCategory.h"
#include "MenuItem.h"
#include "Reconciliation.h"
#include "Inventory.h"
#include "InventoryItem.h"


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
    qmlRegisterType<CashDrawer>("FreePos", 1, 0, "CashDrawer");
    qmlRegisterType<Inventory>("FreePos", 1, 0, "Inventory");
    qmlRegisterType<InventoryItem>("FreePos", 1, 0, "InventoryItem");

    Pos *pos = Pos::instance();    
    pos->readHistory();


    pos->readHistory("currMenu.txt");
    pos->readHistory("currInventory.txt");
    pos->addTestData();

    QQmlApplicationEngine engine;    
    engine.rootContext()->setContextProperty("pos", (QObject*)pos);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));




//    server.openDb();
//    server.createDb();

//    if(server.listen(QHostAddress("127.0.0.1"), 1337)) {
//    //if(server.listen(QHostAddress("192.168.10.73"), 1337)) {
//        qDebug() << "Listening...";
//    } else {
//        qDebug() << "Failed to listen on port.";
//    }


    return app.exec();
}

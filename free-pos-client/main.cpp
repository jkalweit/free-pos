#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Menu.h"
#include "MenuCategory.h"
#include "MenuItem.h"
#include "FreePosClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Menu>("FreePos", 1, 0, "Menu");
    qmlRegisterType<MenuCategory>("FreePos", 1, 0, "MenuCategory");
    qmlRegisterType<MenuItem>("FreePos", 1, 0, "MenuItem");

    Menu menu;
    FreePosClient client(&menu);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("client", (QObject*)&client);
    engine.rootContext()->setContextProperty("menu", (QObject*)&menu);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    client.connectToServer("127.0.0.1", 1337);
    client.getMenuCategories();

    return app.exec();
}

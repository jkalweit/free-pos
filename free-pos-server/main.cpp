#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "FreePosServer.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FreePosServer server;

    QQmlApplicationEngine engine;    
    engine.rootContext()->setContextProperty("server", (QObject*)&server);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    server.openDb();
    server.createDb();
    server.addTestData();

    return app.exec();
}

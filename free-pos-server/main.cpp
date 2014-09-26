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

    if(server.listen(QHostAddress("127.0.0.1"), 1337)) {
        qDebug() << "Listening...";
    } else {
        qDebug() << "Failed to listen on port.";
    }


    return app.exec();
}

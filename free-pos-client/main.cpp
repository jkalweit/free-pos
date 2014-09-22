#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FreePosClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FreePosClient client;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("client", (QObject*)&client);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

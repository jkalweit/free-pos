#include "SimpleServer.h"

#include <QTcpSocket>
#include <QDebug>

SimpleServer::SimpleServer(QObject *parent)
    : QTcpServer(parent)
{
}

void SimpleServer::incomingConnection(qintptr socketfd)
{
    qDebug() << "Incoming connection...";

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    qDebug() << "New client from:" << client->peerAddress().toString();

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void SimpleServer::broadcast(QString msg) {
    foreach(QTcpSocket *client, clients) {
        sendMessage(client, msg);
    }
}

void SimpleServer::sendMessage(QTcpSocket *client, QString msg) {
    qDebug() << "Sending '" << msg << "' to client: " << client->peerAddress();
    client->write(QString(msg + "\n").toUtf8());
}

void SimpleServer::sendData(QTcpSocket *client, QByteArray &data) {
    qDebug() << "Sending QByteArray to client: " << client->peerAddress();
    client->write(data);
}

void SimpleServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString msg = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "Receieved msg:" << msg;

        handleMessage(msg, [&client](QString replyMsg) {
            client->write(QString(replyMsg + "\n").toUtf8());
        });
    }
}


void SimpleServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();

    clients.remove(client);
}


#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H

#include <functional>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QSet>

class SimpleServer : public QTcpServer
{
    Q_OBJECT
    public:
        SimpleServer(QObject *parent=0);

    private slots:
        void readyRead();
        void disconnected();

    protected:
        void incomingConnection(qintptr socketfd);
        virtual void handleMessage(QString msg, std::function<void (QString)> reply) = 0; // QTcpSocket *client) = 0;

        void broadcast(QString msg);
        void sendMessage(QTcpSocket *client, QString msg);
        void sendData(QTcpSocket *client, QByteArray &data);

    private:
        QSet<QTcpSocket*> clients;

};


#endif // SIMPLESERVER_H

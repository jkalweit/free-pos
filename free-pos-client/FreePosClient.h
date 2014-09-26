#ifndef FREEPOSCLIENT_H
#define FREEPOSCLIENT_H

#include <QTcpSocket>
#include <QObject>

class FreePosClient : public QObject
{
    Q_OBJECT
public:
    explicit FreePosClient(QObject *parent = 0);
    Q_INVOKABLE void connectToServer(QString host, quint16 port);

public slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void readMessage();

private:
    QTcpSocket *tcpSocket;
    void sendMessage(QString msg);
    void parseMessage(QString msg);

};


#endif // FREEPOSCLIENT_H

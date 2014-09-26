#ifndef FREEPOSCLIENT_H
#define FREEPOSCLIENT_H

#include <QTcpSocket>
#include <QObject>
#include "FreePosCommand.h"
#include "Menu.h"

class FreePosClient : public QObject
{
    Q_OBJECT    
public:
    explicit FreePosClient(Menu* menu, QObject *parent = 0);
    Q_INVOKABLE void connectToServer(QString host, quint16 port);
    Q_INVOKABLE void getMenuCategories();

    //Menu* menu();

signals:

public slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void readMessage();

private:
    QTcpSocket *tcpSocket;
    Menu* m_menu;
    void sendMessage(QString msg);
    void parseMessage(QString msg);

};


#endif // FREEPOSCLIENT_H

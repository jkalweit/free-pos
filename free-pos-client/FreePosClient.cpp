#include "FreePosClient.h"

#include <QHostAddress>
#include <QDebug>


FreePosClient::FreePosClient(Menu* menu, QObject *parent) :
    QObject(parent), m_menu(menu)
{
}

void FreePosClient::connectToServer(QString host, quint16 port) {
    qDebug() << "Connecting to server...";
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(host), port);
}


void FreePosClient::connected()
{
    qDebug() << "Connected, getting history.";
    //sendMessage(FreePosCommands::HISTORY_REPLAY);
}


void FreePosClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "HostNotFoundError";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "ConnectionRefusedError";
        break;
    default:
        qDebug() << "Error: " << tcpSocket->errorString();
    }
}

void FreePosClient::readMessage()
{
    QString msg;
    QStringList lines;
    while(tcpSocket->canReadLine())
    {
        msg = QString::fromUtf8(tcpSocket->readLine()).trimmed();
        lines = msg.split("/n");
        for(QString line : lines) {
            parseMessage(line);
        }
    }
}





void FreePosClient::parseMessage(QString msg) {
    qDebug() << "Received: " << msg;

    int delimit = msg.indexOf(":");
    QString command = msg.mid(0, delimit);
    QString payload = msg.mid(delimit+1, msg.length() - delimit);

    if(command == FreePosCommand::MENU_ADD_CATEGORY) {
        qDebug() << "Adding menu category: " << payload;
        MenuCategory* category = MenuCategory::deserialize(payload, this);
        m_menu->addCategory(category);
    } else if(command == FreePosCommand::MENU_ADD_ITEM) {
        MenuItem* item = MenuItem::deserialize(payload, this);
        m_menu->addItem(item);
//    } else if(command == FreeBracketCommands::BRACKET_START) {
//        qDebug() << "Starting tournament.";
//        m_bracket->startTournament();
    } else {
        qDebug() << "Unknown Command: " << msg;
    }
}


void FreePosClient::sendMessage(QString msg) {
    tcpSocket->write(QString(msg + "\n").toUtf8());
}

void FreePosClient::getMenuCategories() {
    FreePosCommand command(FreePosCommand::MENU_GET_CATEGORIES);
    tcpSocket->write(QString(command.serialize() + "\n").toUtf8());
}



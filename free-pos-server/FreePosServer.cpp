#include "FreePosServer.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "FreePosCommands.h"

FreePosServer::FreePosServer(QObject *parent) :
    SimpleServer(parent)
{    
}

void FreePosServer::openDb(QString dbname) {
    m_db =  QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbname);
    if (m_db.open()) {
        qDebug() << "DB opened.";
    } else {
        qDebug() << "Could not open DB.";
    }
}

void FreePosServer::createDb() {
    execQuery("CREATE TABLE MenuCategory ( "
                "id INTEGER PRIMARY KEY, "
                "name TEXT "
              ");");
    execQuery("CREATE TABLE MenuItem ( "
                "id INTEGER PRIMARY KEY, "
                "menucategory INTEGER REFERENCES MenuCategory ON DELETE CASCADE NOT NULL, "
                "name TEXT "
              ");");
    execQuery("CREATE INDEX MenuCategoryIndex ON MenuItem(menucategory);");
}

void FreePosServer::addMenuCategory(QString name) {
    QString query = "INSERT INTO MenuCategory ( name ) "
                    "VALUES ( '" + name + "' )";
    execQuery(query);
}

MenuCategory* FreePosServer::getMenuCategory(quint32 id) {
    QSqlQuery query(m_db);
    if(!query.exec("SELECT id, name FROM MenuCategory WHERE id = " + QString::number(id))) {
        qDebug() << "Error executing query: " << query.lastError();
        return nullptr;
    }
    if(query.next()) {
        return new MenuCategory(this, query.value(0).toInt(), query.value(1).toString());
    } else
        return nullptr;

}

void FreePosServer::addMenuItem(quint32 menucategory, QString name) {
    QString query = "INSERT INTO MenuItem ( menucategory, name ) "
                    "VALUES ( " + QString::number(menucategory) + ", '" + name + "' )";
    execQuery(query);
}

void FreePosServer::addTestData() {
    addMenuCategory("Beer");
    addMenuCategory("Appetizers");
    addMenuCategory("Lunch Sandwiches");

    addMenuItem(1, "Bud Light");
    addMenuItem(1, "Miller Light");
    addMenuItem(1, "Coors Light");

    MenuCategory *category = getMenuCategory(1);
    QTextStream d(stdout);
    if(category) {
        d << "   Got category2: ";
        d << *category << endl;

        d << "Serialzed: " << category->serialize() << endl;
        d << "Deserialzed: " << MenuCategory::deserialize(category->serialize(), this)->serialize() << endl;
    } else {
        d << "   ERROR: Could not get category.";
    }

    QByteArray bytes;
    QTextStream stream(bytes, QIODevice::ReadWrite);
    stream << category->serialize() << endl;
    stream.flush();
    stream.seek(0);
    MenuCategory cat2;
    stream >> cat2;
    d << "Cat2: " << cat2.serialize();
}

bool FreePosServer::execQuery(QString sql) {
    qDebug() << "   Executing query: " << sql;

    QSqlQuery query(m_db);
    if(!query.exec(sql)) {
        qDebug() << "Error executing query: " << query.lastError();
        return false;
    }

    return true;
}

FreePosServer::~FreePosServer() {
    m_db.close();
    qDebug() << "DB Closed.";
}

void FreePosServer::handleMessage(QString msg, std::function<void (QString)> reply)
{
    qDebug() << "Handling message in FreeBracketServer...";

    int delimit = msg.indexOf(":");
    QString command = msg.mid(0, delimit);
    QString payload = msg.mid(delimit+1, msg.length() - delimit);

    if(command == FreePosCommands::MENU_GET_CATEGORIES) {
        qDebug() << "Get Menu Categories.";
    }
}

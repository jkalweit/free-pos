#include "FreePosServer.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


FreePosServer::FreePosServer(QObject *parent) :
    SimpleServer(parent), m_currentMenu(nullptr), m_currentRec(nullptr)
{    
}


//int FreePosServer::addReconciliation(QString name) {
//    QString query = "INSERT INTO Reconciliation ( name ) "
//                    "VALUES ( '" + name + "' )";
//    return execInsert(query);
//}

//int FreePosServer::addTicket(quint32 reconciliation, QString name) {
//    QString query = "INSERT INTO Ticket ( reconciliation, name ) "
//                    "VALUES ( " + QString::number(reconciliation) + ", '" + name + "'' )";
//    return execInsert(query);
//}

//int FreePosServer::addMenuCategory(QString name) {
//    QString query = "INSERT INTO MenuCategory ( name ) "
//                    "VALUES ( '" + name + "' )";
//    return execInsert(query);
//}

//MenuCategory* FreePosServer::getMenuCategory(quint32 id) {
//    QSqlQuery query(m_db);
//    if(!query.exec("SELECT id, name FROM MenuCategory WHERE id = " + QString::number(id))) {
//        qDebug() << "Error executing query: " << query.lastError();
//        return nullptr;
//    }
//    if(query.next()) {
//        return new MenuCategory(this, query.value(0).toInt(), query.value(1).toString());
//    } else
//        return nullptr;
//}


//void FreePosServer::addMenuItem(quint32 menucategory, QString name, QString type, float price) {
//    QString query = "INSERT INTO MenuItem ( menucategory, name, type, price ) "
//                    "VALUES ( " + QString::number(menucategory) + ", '" + name + "', '" + type + "', " + QString::number(price) + " )";
//    execQuery(query);
//}



void FreePosServer::handleMessage(QString msg, std::function<void (QString)> reply)
{
    qDebug() << "Handling message in FreePosServer...";

    FreePosCommand command;
    QTextStream stream(&msg);
    stream >> command;

    QTextStream out(stdout);

    out << "Received command: " << command;

    if(command.command() == FreePosCommand::MENU_GET_CATEGORIES) {        
        qDebug() << "   Getting Menu Categories...";
        reply("sup");
//        QSqlQuery query(m_db);
//        if(!query.exec("SELECT id, name FROM MenuCategory")) {
//            qDebug() << "Error executing query: " << query.lastError();
//        }
//        QString replyMsg;
//        QTextStream stream(&replyMsg);
//        while(query.next()) {
//             stream << FreePosCommand::MENU_ADD_CATEGORY << ":" << MenuCategory(this, query.value(0).toInt(), query.value(1).toString());

//        }

//        QSqlQuery query2(m_db);
//        if(!query2.exec("SELECT id, menucategory, name, type, price FROM MenuItem")) {
//            qDebug() << "Error executing query: " << query.lastError();
//        }
//        while(query2.next()) {
//             stream << FreePosCommand::MENU_ADD_ITEM << ":" << MenuItem(this, query2.value(0).toInt(), query2.value(1).toInt(), query2.value(2).toString(), query2.value(3).toString(), query2.value(4).toFloat());
//        }

//        stream.flush();
//        reply(replyMsg);
    }        
}






//void FreePosServer::openDb(QString dbname) {
//    m_db =  QSqlDatabase::addDatabase("QSQLITE");
//    m_db.setDatabaseName(dbname);
//    if (m_db.open()) {
//        qDebug() << "DB opened.";
//    } else {
//        qDebug() << "Could not open DB.";
//    }
//}

//void FreePosServer::createDb() {
//    execQuery("CREATE TABLE Reconciliation ( "
//                "id INTEGER PRIMARY KEY, "
//                "name TEXT "
//              ");");
//    execQuery("CREATE TABLE Ticket ( "
//                "id INTEGER PRIMARY KEY, "
//                "reconciliation INTEGER REFERENCES Reconciliation ON DELETE CASCADE NOT NULL, "
//                "name TEXT "
//              ");");
//    execQuery("CREATE INDEX TicketReconciliationIndex ON Ticket(reconciliation);");
//    execQuery("CREATE TABLE Customer ( "
//                "id INTEGER PRIMARY KEY, "
//                "ticket INTEGER REFERENCES Ticket ON DELETE CASCADE NOT NULL, "
//                "name TEXT "
//              ");");
//    execQuery("CREATE INDEX CustomerTicketIndex ON Customer(ticket);");
//    execQuery("CREATE TABLE MenuCategory ( "
//                "id INTEGER PRIMARY KEY, "
//                "name TEXT "
//              ");");
//    execQuery("CREATE TABLE MenuItem ( "
//                "id INTEGER PRIMARY KEY, "
//                "menucategory INTEGER REFERENCES MenuCategory ON DELETE CASCADE NOT NULL, "
//                "name TEXT, "
//                "type TEXT, "
//                "price REAL"
//              ");");
//    execQuery("CREATE INDEX MenuItemMenuCategoryIndex ON MenuItem(menucategory);");
//}

void FreePosServer::setCurrentMenu(Menu *menu) {
    m_currentMenu = menu;
    currentMenuChanged(m_currentMenu);
}

Menu* FreePosServer::getCurrentMenu() {
    return m_currentMenu;
}

void FreePosServer::setCurrentRec(Reconciliation *rec) {
    m_currentRec = rec;
    currentRecChanged(m_currentRec);
}

Reconciliation* FreePosServer::getCurrentRec() {
    return m_currentRec;
}

void FreePosServer::addTestData() {
//    addMenuCategory("Beer");
//    addMenuCategory("Appetizers");
//    addMenuCategory("Lunch Sandwiches");



//    addMenuItem(1, "Bud Light", "Alcohol", 2.75);
//    addMenuItem(1, "Miller Light", "Alcohol", 2.75);
//    addMenuItem(1, "Coors Light", "Alcohol", 2.75);

    Ticket *ticket = m_currentRec->addTicket("1-1");
    ticket->addCustomer("Andrew");
    ticket = m_currentRec->addTicket("2-2");
    ticket->addCustomer("Justin");
    ticket = m_currentRec->addTicket("Bar");
    Customer *customer = ticket->addCustomer("Larry");
    customer->addOrderItem("Steak Bites - Small", "Food", 7.50, 2, "This is a note.");
    customer->addOrderItem("Steak Bites - Small", "Food", 7.50, 1, "This is a note2.");
    customer = ticket->addCustomer("Steve");
    customer->addOrderItem("Steak Bites - Large", "Food", 8.00, 0.5, "This is a note3.");

    ticket = m_currentRec->addTicket("Deck");
    ticket->addCustomer("Tina");

    MenuCategory* cat = m_currentMenu->addCategory("Bottle Beer");
    cat->addMenuItem("Bud Light", "Alcohol", 2.75);
    cat->addMenuItem("Miller Lite", "Alcohol", 2.75);
    cat->addMenuItem("Coors Light", "Alcohol", 2.75);
    m_currentMenu->addCategory("Draft Beer");
    cat = m_currentMenu->addCategory("Lunch Entrees");
    cat->addMenuItem("Chicken Tenders", "Food", 9.00);
    cat->addMenuItem("Cheeseburger", "Food", 9.00);

    m_currentMenu->addCategory("Lunch Sandwiches");
    m_currentMenu->addCategory("Lunch Sides");

    m_currentRec->setSelectedTicket(ticket);
    m_currentMenu->setSelectedCategory(cat);

    //int recId = addReconciliation("Test Rec");
}


//bool FreePosServer::execQuery(QString sql) {
//    qDebug() << "   Executing query: " << sql;

//    QSqlQuery query(m_db);
//    if(!query.exec(sql)) {
//        qDebug() << "Error executing query: " << query.lastError();
//        return false;
//    }

//    return true;
//}

//int FreePosServer::execInsert(QString sql) {
//    qDebug() << "   Executing INSERT query: " << sql;

//    QSqlQuery query(m_db);
//    if(!query.exec(sql)) {
//        qDebug() << "Error executing query: " << query.lastError();
//        return -1;
//    } else {
//        return query.lastInsertId().toInt();
//    }
//}


//FreePosServer::~FreePosServer() {
//    m_db.close();
//    qDebug() << "DB Closed.";
//}

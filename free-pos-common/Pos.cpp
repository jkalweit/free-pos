#include "Pos.h"
#include "Ticket.h"
#include "Customer.h"
#include "OrderItem.h"


#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>







Pos::Pos(QObject *parent) :
    QObject(parent), m_selectedMenu(nullptr), m_selectedRec(nullptr)
{
}


QQmlListProperty<Menu> Pos::menus() {
    return QQmlListProperty<Menu>(this, m_menus);
}

void Pos::addMenu(Menu* menu) {
    m_menus.append(menu);
    menusChanged(menus());
}

QQmlListProperty<Reconciliation> Pos::reconciliations() {
    return QQmlListProperty<Reconciliation>(this, m_reconciliations);
}

Reconciliation* Pos::openNewRec() {
    Reconciliation* rec = new Reconciliation(this, 0, "Lunch", "", QDateTime::currentDateTime());
    addReconciliation(rec);
    return rec;
}

void Pos::addReconciliation(Reconciliation *rec) {
    m_reconciliations.append(rec);
    reconciliationsChanged(reconciliations());
}

void Pos::addTestData() {

    m_selectedMenu = new Menu(this);
    addMenu(m_selectedMenu);
    selectedMenuChanged(m_selectedMenu);

//    m_selectedRec = openNewRec();
//    selectedRecChanged(m_selectedRec);

//    Ticket *ticket = m_selectedRec->addTicket("1-1");
////    ticket->addCustomer("Andrew");
////    ticket = m_selectedRec->addTicket("2-2");
////    ticket->addCustomer("Justin");
////    ticket = m_selectedRec->addTicket("Bar");
//    Customer *customer = ticket->addCustomer("Larry");
//    customer->addOrderItem("Steak Bites - Small", "Food", 7.50, 2, "This is a note.");
//    customer->addOrderItem("Steak Bites - Small", "Food", 7.50, 1, "This is a note2.");
//    customer = ticket->addCustomer("Steve");
//    customer->addOrderItem("Steak Bites - Large", "Food", 8.00, 0.5, "This is a note3.");

////    ticket = m_selectedRec->addTicket("Deck");
////    ticket->addCustomer("Tina");
//    m_selectedRec->setSelectedTicket(ticket);

////    for(int i = 1; i <= 50; i++) {
////        ticket = m_selectedRec->addTicket("Bar");
////        customer = ticket->addCustomer("Test Customer " + QString::number(i));
////        for(int j = 0; j < 1; j++) {
////            customer->addOrderItem("Test Food Item", "Food", 7.50, 1, "This is a note.");
////            customer->addOrderItem("Test Alcohol Item", "Alcohol", 2.75, 1, "This is a note.");
////        }
////    }




    QFile file("../../free-pos/free-pos-server/menu.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open menu file" << endl;
    }

    QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    QJsonObject menu = json.object()["categories"].toObject();
    QJsonObject catObj;
    QJsonObject itemObj;
    MenuCategory* newCat;
    //    cat->addMenuItem("Bud Light", "Alcohol", 2.75);

    for(QJsonValue cat : menu) {
        catObj = cat.toObject();
        //qDebug() << "Adding: " << catObj["name"].toString();
        newCat = m_selectedMenu->addCategory(catObj["name"].toString());
        for(QJsonValue item : catObj["menuitems"].toObject()) {
            itemObj = item.toObject();
            newCat->addMenuItem(itemObj["name"].toString(), itemObj["class"].toString(), itemObj["price"].toString().toFloat());
        }
    }
}

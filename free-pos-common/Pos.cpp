#include "Pos.h"
#include "Ticket.h"
#include "Customer.h"
#include "OrderItem.h"


#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>



Pos* Pos::s_instance = nullptr;



Pos* Pos::instance()
{
    if(!s_instance) {
        qDebug() << "Creating singleton...";
        s_instance = new Pos();
    }

    return Pos::s_instance;
}



Pos::Pos(QObject *parent) :
    QObject(parent), m_isHistoryDisabled(false), m_selectedMenu(nullptr), m_selectedRec(nullptr)
{
}

void Pos::readHistory() {

    m_isHistoryDisabled = true;

    QFile file("./history.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        int delimit = line.indexOf(":");
        QString command = line.mid(0, delimit);
        QString payload = line.mid(delimit+1, line.length() - delimit);

        if(command == "OpenRec") {
            qDebug() << "Open new rec" << payload;
            m_selectedRec = Reconciliation::deserialize(payload, this);
        } else if(command == "AddTicket") {
            qDebug() << "AddTicket: " << payload;
            m_selectedRec->addTicket(Ticket::deserialize(payload, this));
        } else if(command == "AddCustomer") {
            qDebug() << "AddCustomer: " << payload;

            Customer *c = Customer::deserialize(payload, this);
            Ticket *ticket = m_selectedRec->getTicket(c->property("ticketId").toInt());
            if(ticket)
                ticket->addCustomer(c);
            else
                qDebug() << "Ticket does not exist.";
        } else if(command == "AddOrderItem") {
            qDebug() << "AddOrderItem: " << payload;

            OrderItem *i = OrderItem::deserialize(payload);
            Ticket *ticket = m_selectedRec->getTicket(i->property("ticketId").toInt());
            if(!ticket) {
                qDebug() << "Ticket does not exist.";
                return;
            }
            Customer *customer = ticket->getCustomer(i->property("customerId").toUInt());
            if(!customer) {
                qDebug() << "Customer does not exist.";
                return;
            }
            customer->addOrderItem(i);
        } else if (command == "UpdateTicket") {
            qDebug() << "UpdateTicket: " << payload;
            QStringList split = payload.split(":");
            quint32 ticketId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            QString restored = value.replace("\\n", "\n").replace("\\colon", ":");
            Ticket* ticket = m_selectedRec->getTicket(ticketId);
            ticket->setProperty(property.toUtf8().data(), restored);
        } else if (command == "UpdateCustomer") {
            qDebug() << "UpdateCustomer: " << payload;
            QStringList split = payload.split(":");
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            QString property = split[2];
            QString value = split[3];
            QString restored = value.replace("\\n", "\n").replace("\\colon", ":");
            Customer* customer = m_selectedRec->getTicket(ticketId)->getCustomer(customerId);
            customer->setProperty(property.toUtf8().data(), restored);
        } else if (command == "UpdateOrderItem") {
            qDebug() << "UpdateOrderItem: " << payload;
            QStringList split = payload.split(":");
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            QString property = split[3];
            QString value = split[4];
            OrderItem* orderItem = m_selectedRec->getTicket(ticketId)->getCustomer(customerId)->getOrderItem(orderItemId);
            QString restored = value.replace("\\n", "\n").replace("\\colon", ":");
            orderItem->setProperty(property.toUtf8().data(), restored);
        } else {
            qDebug() << "Unknown command: " << command << " " << payload;
        }
    }

    // optional, as QFile destructor will already do it:
    file.close();

    m_isHistoryDisabled = false;
}

void Pos::appendToHistory(QString item) {
    if(m_isHistoryDisabled)
        return;

    QFile file("./history.txt");
    file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << item << endl;
    file.close();
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
    appendToHistory("OpenRec:" + rec->serialize());
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

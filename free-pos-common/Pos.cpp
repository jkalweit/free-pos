#include "Pos.h"
#include "Ticket.h"
#include "Customer.h"
#include "OrderItem.h"


#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QDateTime>


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

void Pos::readHistory(QString filename) {

    m_isHistoryDisabled = true;

    QDir().mkdir("data");

    QFile file("./data/" + filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        int delimit = line.indexOf(":");
        QString timestamp = line.mid(0, delimit);
        Q_UNUSED(timestamp);
        QString theRest = line.mid(delimit+1, line.length() - delimit);
        delimit = theRest.indexOf(":");
        QString command = theRest.mid(0, delimit);
        QString payload = theRest.mid(delimit+1, line.length() - delimit);
        QStringList split = SimpleSerializable::deserializeList(payload);

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
        } else if (command == "UpdateReconciliation") {
            qDebug() << "UpdateReconciliation: " << payload;
            //quint32 recId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            m_selectedRec->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateCashDrawer") {
            qDebug() << "UpdateCashDrawer: " << payload;
            //quint32 recId = split[0].toUInt();
            quint32 cashDrawerId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            if(cashDrawerId == 1) {
                m_selectedRec->beginningDrawer()->setProperty(property.toUtf8().data(), value);
            } else if(cashDrawerId == 2) {
                m_selectedRec->endingDrawer()->setProperty(property.toUtf8().data(), value);
            }
        } else if (command == "UpdateTicket") {
            qDebug() << "UpdateTicket: " << payload;            
            quint32 ticketId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            Ticket* ticket = m_selectedRec->getTicket(ticketId);
            ticket->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateCustomer") {
            qDebug() << "UpdateCustomer: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            QString property = split[2];
            QString value = split[3];
            Customer* customer = m_selectedRec->getTicket(ticketId)->getCustomer(customerId);
            customer->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateOrderItem") {
            qDebug() << "UpdateOrderItem: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            QString property = split[3];
            QString value = split[4];
            OrderItem* orderItem = m_selectedRec->getTicket(ticketId)->getCustomer(customerId)->getOrderItem(orderItemId);
            orderItem->setProperty(property.toUtf8().data(), value);
        } else if (command == "AddMenu") {
            qDebug() << "AddMenu: " << payload;
            //quint32 id = split[0].toUInt();
            m_selectedMenu = new Menu(this);
            Pos::instance()->addMenu(m_selectedMenu);
            selectedMenuChanged(m_selectedMenu);
        } else if(command == "AddMenuCategory") {
            qDebug() << "AddMenuCategory: " << payload;
            quint32 id = split[0].toUInt();
            QString name = split[1];
            m_selectedMenu->addCategory(new MenuCategory(this, id, name));
        } else if(command == "AddMenuItem") {
            qDebug() << "AddMenuItem: " << payload;
            quint32 id = split[0].toUInt();
            quint32 menuCategoryId = split[1].toUInt();
            QString name = split[2];
            QString type = split[3];
            float price = split[4].toFloat();
            MenuCategory *category = m_selectedMenu->getMenuCategory(menuCategoryId);
            category->addMenuItem(new MenuItem(this, id, menuCategoryId, name, type, price));
        } else if (command == "UpdateMenuCategory") {
            qDebug() << "UpdateMenuCategory: " << payload;
            quint32 menuCategoryId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            MenuCategory* cat = m_selectedMenu->getMenuCategory(menuCategoryId);
            cat->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateMenuItem") {
            qDebug() << "UpdateMenuItem: " << payload;
            quint32 id = split[0].toUInt();
            quint32 menuCategoryId = split[1].toUInt();
            QString property = split[2];
            QString value = split[3];
            MenuCategory *cat = m_selectedMenu->getMenuCategory(menuCategoryId);
            MenuItem *item = cat->getMenuItem(id);
            item->setProperty(property.toUtf8().data(), value);
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
    appendToFile(item, "currRec.txt");
}

void Pos::appendToMenuHistory(QString item) {
    if(m_isHistoryDisabled)
        return;
    appendToFile(item, "currMenu.txt");
}

void Pos::appendToFile(QString item, QString filename) {
    QFile file("./data/" + filename);
    file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << SimpleSerializable::escapeString(QDateTime::currentDateTime().toString()) << ":" << item << endl;
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

Reconciliation* Pos::selectedRec() {
    return m_selectedRec;
}

bool Pos::closeCurrentRec() {
    if(!m_selectedRec) {
        qDebug() << "No current rec.";
        return false;
    }
    if(m_selectedRec->isOpen()) {
        qDebug() << "Rec is still open.";
        return false;
    }

    QString newLocation = "./data/" + m_selectedRec->fileName();
    qDebug() << "Moving rec to " << newLocation;
    if(QDir().exists(newLocation)) {
        qDebug() << "File already exists.";
        QMessageBox::about(nullptr, "Error", "Cannot close rec: file already exists: " + newLocation);
        return false;
    }

    QDir().rename("./data/currRec.txt", newLocation);
    return true;
}

void Pos::addReconciliation(Reconciliation *rec) {
    m_reconciliations.append(rec);
    reconciliationsChanged(reconciliations());
}



void Pos::addTestData() {

//    m_selectedMenu = new Menu(this);
//    addMenu(m_selectedMenu);
//    selectedMenuChanged(m_selectedMenu);

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




//#ifdef QT_DEBUG
//    QFile file("../../free-pos/free-pos-server/menu.json");
//#else
//    QFile file("menu.json");
//#endif

//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "Could not open menu file" << endl;
//    }

//    QJsonDocument json = QJsonDocument::fromJson(file.readAll());
//    QJsonObject menu = json.object()["categories"].toObject();
//    QJsonObject catObj;
//    QJsonObject itemObj;
//    MenuCategory* newCat;


//    for(QJsonValue cat : menu) {
//        catObj = cat.toObject();
//        //qDebug() << "Adding: " << catObj["name"].toString();
//        newCat = m_selectedMenu->addCategory(catObj["name"].toString());
//        for(QJsonValue item : catObj["menuitems"].toObject()) {
//            itemObj = item.toObject();
//            newCat->addMenuItem(itemObj["name"].toString(), itemObj["class"].toString(), itemObj["price"].toString().toFloat());
//        }
//    }
}

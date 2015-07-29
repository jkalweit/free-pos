#include "WebServiceController.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QUuid>

#include "Reconciliation.h"
#include "Ticket.h"
#include "Pos.h"

WebServiceController::WebServiceController(QObject *parent) :
    QObject(parent)
{
}

void WebServiceController::sendReconciliation(Reconciliation *rec) {

    QUrl url("http://coalyard.azure-mobile.net/tables/Reconciliation");
    //QUrl url("http://localhost:12509/tables/Reconciliation");
    url.setUserName("");
    url.setPassword("XzknuDmYLwaJCTzznRUnRErOIPjJnq59");

    QUrlQuery postData;
    postData.addQueryItem("salesDate", rec->date().toString());
    postData.addQueryItem("description", rec->name());
    postData.addQueryItem("foodSales", QString::number(rec->foodTotal() + rec->taxTotal()));
    postData.addQueryItem("barSales", QString::number(rec->barTotal()));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleSimpleReply(QNetworkReply*)));
    qDebug() << "Sending request: " << postData.toString(QUrl::FullyEncoded).toUtf8();
    m_manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    qDebug() << "Sent request!";
}


void WebServiceController::sendKitchenOrder(Ticket *ticket) {

    QUrl url("http://localhost:1337/api/kitchen_orders");
//    QUrl url("http://localhost:56881/tables/KitchenOrder");
//    QUrl url("http://rmscoalyard.azure-mobile.net/tables/KitchenOrder");
//    url.setUserName("");
//    url.setPassword("THWNiNTAOaSAviPfKJwUlmHHxeuDdM42");



    //QUrlQuery postData;
//    postData.addQueryItem("salesDate", rec->date().toString());
//    postData.addQueryItem("description", rec->name());
//    postData.addQueryItem("foodSales", QString::number(rec->foodTotal() + rec->taxTotal()));
//    postData.addQueryItem("barSales", QString::number(rec->barTotal()));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleSimpleReply(QNetworkReply*)));

    QByteArray orderGuid = QUuid().createUuid().toByteArray();


    QByteArray data = "{";
    //data += "id: '" + orderGuid + "',";
    data += "\"isTogo\": " + ticket->property("isTogo").toByteArray() + ",";
    QList<Customer*> customers = ticket->customersList();
    Customer *firstCustomer = customers[0];
    data += "\"name\": \"" + firstCustomer->property("name").toByteArray() + "\",";
    data += "\"location\": \"" + ticket->property("name").toByteArray() + "\",";
    data += "\"kitchenOrderItems\": [";
    int itemCount = 0;
    for(Customer *c : ticket->customersList()) {
        for(OrderItem *i : c->orderItemsList()) {
            QByteArray itemGuid = QUuid().createUuid().toByteArray();
            if(!i->property("deleted").toBool() && i->property("type").toString() != "Alcohol" && !i->isSubmitted()) {
                if(itemCount > 0) data += ",";
                data += "{";
                    //data += "\"id\": \"" + itemGuid + "\",";
                    //data += "\"kitchenOrderId\": \"" + orderGuid + "\",";
                    data += "\"addedToOrderAt\": \"" + i->property("createdStamp").toDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz") + "\",";
                    data += "\"description\": \"" + i->property("name").toByteArray() + "\",";
                    data += "\"note\": \"" + i->property("note").toByteArray() + "\",";
                    data += "\"type\": \"" + i->property("type").toByteArray() + "\",";
                    data += "\"prepType\": \"" + i->prepType() + "\",";
                    data += "\"quantity\": " + i->property("quantity").toByteArray() + ",";
                        data += "\"kitchenOrderItemOptions\": [";
                        int optionCount = 0;
                        for(OrderItemOption *o : i->orderItemOptionsList()){
                            if(optionCount > 0) data += ",";
                            data += "{";
//                            data += "\"id\": \"" + QUuid().createUuid().toByteArray() + "\",";
//                            data += "\"kitchenOrderItemId\": \"" + itemGuid + "\",";
                            data += "\"sortOrder\": " + QString::number(optionCount) + ",";
                            data += "\"type\": \"Option\",",
                            data += "\"prepType\": \"" + o->prepType() + "\",";
                            data += "\"description\": \"" + o->property("name").toByteArray() + ": " + o->property("menuItemName").toByteArray() + "\"";
                            data += "}";
                            optionCount++;
                        }
                        for(OrderItemInventoryItem *inv : i->orderItemInventoryItemsList()){
                            if(inv->isAdded() || inv->isRemoved()) {
                                if(optionCount > 0) data += ",";
                                data += "{";
//                                data += "\"id\": \"" + QUuid().createUuid().toByteArray() + "\",";
//                                data += "\"kitchenOrderItemId: \"" + itemGuid + "\",";
                                data += "\"sortOrder\": " + QString::number(optionCount) + ",";
                                data += "\"description\": \"" + inv->property("name").toByteArray() + "\",";
                                if(inv->isAdded()) data += "\"type\": \"Add\"";
                                else if(inv->isRemoved()) data += "\"type\": \"Remove\"";
                                data += "}";
                                optionCount++;
                            }
                        }
                        data += "]";
                data += "}";
                itemCount++;
            }
        }
    }
    data += "]";
    data += "}";
    QString message;
    if(itemCount > 0) {
        message = "Sending request: " + data;
        qDebug() << message;
        m_manager->post(request, data);
        qDebug() << "Sent request!";
    } else {
        message = "No items to send. Not sending request.";
        qDebug() << message;
    }

    Pos::instance()->appendToWebServiceLog(message);
}


void WebServiceController::handleSimpleReply(QNetworkReply *reply){
    QByteArray text = reply->readAll();
    QString message = "Success: " + text;
    if(text.startsWith("{\"ok\":1")) {
        qDebug() << message;
    } else {        
        message = "Failed to send request.\n\n" + text;
        qDebug() << message;
        Pos::instance()->showDialogMessage(message);
    }

    Pos::instance()->appendToWebServiceLog(message);
}

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

#include "Reconciliation.h"


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

void WebServiceController::handleSimpleReply(QNetworkReply *reply){
    qDebug() << "Simple reply: " << reply->readAll();
}

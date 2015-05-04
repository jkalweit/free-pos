#ifndef WEBSERVICECONTROLLER_H
#define WEBSERVICECONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Reconciliation;

class WebServiceController : public QObject
{
    Q_OBJECT
public:
    explicit WebServiceController(QObject *parent = 0);

    void sendReconciliation(Reconciliation *rec);

signals:

public slots:
    void handleSimpleReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
};

#endif // WEBSERVICECONTROLLER_H

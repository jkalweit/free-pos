#ifndef LOYALTYMEMBER_H
#define LOYALTYMEMBER_H

#include <QObject>
#include <QQmlListProperty>

class LoyaltyMember : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString firstName MEMBER m_firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName MEMBER m_lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString emailAddress MEMBER m_emailAddress READ emailAddress WRITE setEmailAddress NOTIFY emailAddressChanged)
    Q_PROPERTY(float pointsBalance MEMBER m_pointsBalance READ pointsBalance NOTIFY pointsBalanceChanged)

public:
    explicit LoyaltyMember(QObject *parent = 0, QString id = "", QString firstName = "", QString lastName = "", QString emailAddress = "", float pointsBalance = 0);

    QString id();
    QString firstName();
    QString lastName();
    QString emailAddress();
    float pointsBalance();

    void setFirstName(QString value);
    void setLastName(QString value);
    void setEmailAddress(QString value);



signals:
    void idChanged(QString);
    void firstNameChanged(QString);
    void lastNameChanged(QString);
    void emailAddressChanged(QString);
    void pointsBalanceChanged(float);


public slots:

private:
    QString m_id;
    QString m_firstName;
    QString m_lastName;
    QString m_emailAddress;
    float m_pointsBalance;


};

#endif // LOYALTYMEMBER_H

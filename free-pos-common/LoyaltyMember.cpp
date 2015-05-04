#include "LoyaltyMember.h"

#include <QMetaProperty>
#include <QDebug>

LoyaltyMember::LoyaltyMember(QObject *parent, QString id, QString firstName, QString lastName, QString emailAddress, float pointsBalance) :
    QObject(parent), m_id(id), m_firstName(firstName), m_lastName(lastName), m_emailAddress(emailAddress), m_pointsBalance(pointsBalance)
{
}

QString LoyaltyMember::id() {
    return m_id;
}

QString LoyaltyMember::firstName() {
    return m_firstName;
}

QString LoyaltyMember::lastName() {
    return m_lastName;
}

QString LoyaltyMember::emailAddress() {
    return m_emailAddress;
}

float LoyaltyMember::pointsBalance() {
    return m_pointsBalance;
}


void LoyaltyMember::setFirstName(QString value) {
    if(m_firstName != value) {
        m_firstName = value;
        firstNameChanged(m_firstName);
    }
}

void LoyaltyMember::setLastName(QString value) {
    if(m_lastName != value) {
        m_lastName = value;
        lastNameChanged(m_lastName);
    }
}

void LoyaltyMember::setEmailAddress(QString value) {
    if(m_emailAddress != value) {
        m_emailAddress = value;
        emailAddressChanged(m_emailAddress);
    }
}




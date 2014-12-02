#ifndef SIMPLESERIALIZABLE_H
#define SIMPLESERIALIZABLE_H

#include <QStringList>
#include <QObject>

class SimpleSerializable : public QObject
{
    Q_OBJECT
public:
    explicit SimpleSerializable(QObject *parent = 0);

    virtual QStringList updatePrefix() = 0;

    static QString escapeString(QString val);
    static QString unEscapeString(QString val);
    static QString serializeList(QStringList vals);
    static QStringList deserializeList(QString vals);
signals:

public slots:

protected:
    void logPropertyChanged(QVariant value, QString propertyName);
    void logMenuPropertyChanged(QVariant value, QString propertyName);
    void logInventoryPropertyChanged(QVariant value, QString propertyName);
    void logTrackerPropertyChanged(QVariant value, QString propertyName);
    void logFixedCostPropertyChanged(QVariant value, QString propertyName);

};

#endif // SIMPLESERIALIZABLE_H

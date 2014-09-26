#ifndef MENUCATEGORY_H
#define MENUCATEGORY_H

#include <QTextStream>
#include <QObject>

class MenuCategory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
public:
    explicit MenuCategory(QObject *parent = 0, quint32 id = 0, QString name = "");
    QString serialize() const;
    static MenuCategory* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const MenuCategory& category);
    friend QTextStream& operator>>(QTextStream& stream, MenuCategory& category);

signals:
    void idChanged(quint32);
    void nameChanged(QString);

public slots:

private:
    quint32 m_id;
    QString m_name;
};

#endif // MENUCATEGORY_H

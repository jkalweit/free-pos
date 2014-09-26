#ifndef MENUITEM_H
#define MENUITEM_H

#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>

class MenuItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
public:
    explicit MenuItem(QObject *parent = 0, quint32 id = 0, quint32 menuCategoryId = 0, QString name = "");

    quint32 menuCategoryId();

    QString serialize() const;
    static MenuItem* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const MenuItem& obj);
    friend QTextStream& operator>>(QTextStream& stream, MenuItem& obj);

signals:
    void idChanged(quint32);
    void nameChanged(QString);

public slots:

private:
    quint32 m_id;
    quint32 m_menuCategoryId;
    QString m_name;
};

#endif // MENUITEM_H

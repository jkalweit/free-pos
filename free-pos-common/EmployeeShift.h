#ifndef EMPLOYEESHIFT_H
#define EMPLOYEESHIFT_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class EmployeeShift : public SimpleSerializable
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString note MEMBER m_note READ note WRITE setNote NOTIFY noteChanged)
    Q_PROPERTY(float wage MEMBER m_wage READ wage WRITE setWage NOTIFY wageChanged)
    Q_PROPERTY(quint8 scheduledStartHour MEMBER m_scheduledStartHour READ scheduledStartHour WRITE setScheduledStartHour NOTIFY scheduledStartHourChanged)
    Q_PROPERTY(quint8 scheduledStartMinute MEMBER m_scheduledStartMinute READ scheduledStartMinute WRITE setScheduledStartMinute NOTIFY scheduledStartMinuteChanged)
    Q_PROPERTY(bool scheduledStartAM MEMBER m_scheduledStartAM READ scheduledStartAM WRITE setScheduledStartAM NOTIFY scheduledStartAMChanged)
    Q_PROPERTY(quint8 scheduledEndHour MEMBER m_scheduledEndHour READ scheduledEndHour WRITE setScheduledEndHour NOTIFY scheduledEndHourChanged)
    Q_PROPERTY(quint8 scheduledEndMinute MEMBER m_scheduledEndMinute READ scheduledEndMinute WRITE setScheduledEndMinute NOTIFY scheduledEndMinuteChanged)
    Q_PROPERTY(bool scheduledEndAM MEMBER m_scheduledEndAM READ scheduledEndAM WRITE setScheduledEndAM NOTIFY scheduledEndAMChanged)
    Q_PROPERTY(quint8 startHour MEMBER m_startHour READ startHour WRITE setStartHour NOTIFY startHourChanged)
    Q_PROPERTY(quint8 startMinute MEMBER m_startMinute READ startMinute WRITE setStartMinute NOTIFY startMinuteChanged)
    Q_PROPERTY(bool startAM MEMBER m_startAM READ startAM WRITE setStartAM NOTIFY startAMChanged)
    Q_PROPERTY(quint8 endHour MEMBER m_endHour READ endHour WRITE setEndHour NOTIFY endHourChanged)
    Q_PROPERTY(quint8 endMinute MEMBER m_endMinute READ endMinute WRITE setEndMinute NOTIFY endMinuteChanged)
    Q_PROPERTY(bool endAM MEMBER m_endAM READ endAM WRITE setEndAM NOTIFY endAMChanged)

    Q_PROPERTY(float cost READ cost NOTIFY costChanged)

    Q_PROPERTY(QString scheduledStartFormatted READ scheduledStartFormatted NOTIFY scheduledStartFormattedChanged)
    Q_PROPERTY(QString scheduledEndFormatted READ scheduledEndFormatted NOTIFY scheduledEndFormattedChanged)
    Q_PROPERTY(QString startFormatted READ startFormatted NOTIFY startFormattedChanged)
    Q_PROPERTY(QString endFormatted READ endFormatted NOTIFY endFormattedChanged)
    Q_PROPERTY(QString scheduledOrActualStartFormatted READ scheduledOrActualStartFormatted NOTIFY scheduledOrActualStartFormattedChanged)
    Q_PROPERTY(QString scheduledOrActualEndFormatted READ scheduledOrActualEndFormatted NOTIFY scheduledOrActualEndFormattedChanged)
    Q_PROPERTY(float scheduledHours READ scheduledHours NOTIFY scheduledHoursChanged)
    //Q_PROPERTY(float actualHours READ actualHours NOTIFY actualHoursChanged)
    Q_PROPERTY(float scheduledOrActualHours READ scheduledOrActualHours NOTIFY scheduledOrActualHoursChanged)
    //Q_PROPERTY(QString scheduledHoursFormatted READ scheduledHoursFormatted NOTIFY scheduledHoursFormattedChanged)
    Q_PROPERTY(bool isClockedIn READ isClockedIn NOTIFY isClockedInChanged)
    Q_PROPERTY(bool isClockedOut READ isClockedOut NOTIFY isClockedOutChanged)
    Q_PROPERTY(bool canClockIn READ canClockIn NOTIFY canClockInChanged)
    Q_PROPERTY(bool canClockOut READ canClockOut NOTIFY canClockOutChanged)
public:
    explicit EmployeeShift(QObject *parent = 0, quint32 id = 0, QString name = "", QString note = "", float wage = 0, quint8 scheduledStartHour = 0, quint8 scheduledStartMinute = 0, bool scheduledStartAM = false, quint8 scheduledEndHour = 0, quint8 scheduledEndMinute = 0, bool scheduledEndAM = false, quint8 startHour = 0, quint8 startMinute = 0, bool startAM = false, quint8 endHour = 0, quint8 endMinute = 0, bool endAM = false);

    virtual QStringList updatePrefix();

    quint32 id();
    QString name();
    QString note();
    float wage();
    quint8 scheduledStartHour();
    quint8 scheduledStartMinute();
    bool scheduledStartAM();
    quint8 scheduledEndHour();
    quint8 scheduledEndMinute();
    bool scheduledEndAM();
    quint8 startHour();
    quint8 startMinute();
    bool startAM();
    quint8 endHour();
    quint8 endMinute();
    bool endAM();

    void setName(QString value);
    void setNote(QString value);
    void setWage(float value);
    void setScheduledStartHour(quint8 value);
    void setScheduledStartMinute(quint8 value);
    void setScheduledStartAM(bool value);
    void setScheduledEndHour(quint8 value);
    void setScheduledEndMinute(quint8 value);
    void setScheduledEndAM(bool value);
    void setStartHour(quint8 value);
    void setStartMinute(quint8 value);
    void setStartAM(bool value);
    void setEndHour(quint8 value);
    void setEndMinute(quint8 value);
    void setEndAM(bool value);

    float cost();

    QString scheduledStartFormatted();
    QString scheduledEndFormatted();
    QString startFormatted();
    QString endFormatted();
    float scheduledHours();
    //float actualHours();
    float scheduledOrActualHours();
    QString scheduledOrActualStartFormatted();
    QString scheduledOrActualEndFormatted();
    bool isClockedIn();
    bool isClockedOut();
    bool canClockIn();
    bool canClockOut();
    Q_INVOKABLE void clockIn();
    Q_INVOKABLE void clockOut();

    QString serialize() const;
    static EmployeeShift* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void noteChanged(QString);
    void wageChanged(float);
    void scheduledStartHourChanged(quint8);
    void scheduledStartMinuteChanged(quint8);
    void scheduledStartAMChanged(bool);
    void scheduledEndHourChanged(quint8);
    void scheduledEndMinuteChanged(quint8);
    void scheduledEndAMChanged(bool);
    void startHourChanged(quint8);
    void startMinuteChanged(quint8);
    void startAMChanged(bool);
    void endHourChanged(quint8);
    void endMinuteChanged(quint8);
    void endAMChanged(bool);

    void costChanged(float);

    void scheduledStartFormattedChanged(QString);
    void scheduledEndFormattedChanged(QString);
    void startFormattedChanged(QString);
    void endFormattedChanged(QString);
    void scheduledHoursChanged(float);
    //void actualHoursChanged(float);
    void scheduledOrActualHoursChanged(float);
    void canClockInChanged(bool);
    void canClockOutChanged(bool);
    void isClockedInChanged(bool);
    void isClockedOutChanged(bool);
    void scheduledOrActualStartFormattedChanged(QString);
    void scheduledOrActualEndFormattedChanged(QString);
public slots:
    void fireScheduledStartChanged();
    void fireScheduledEndChanged();
    void fireStartChanged();
    void fireEndChanged();
protected:
    virtual void logPropertyChanged(QVariant value, QString propertyName) override;
private:
    quint32 m_id;
    QString m_name;
    QString m_note;
    float m_wage;
    quint8 m_scheduledStartHour;
    quint8 m_scheduledStartMinute;
    bool m_scheduledStartAM;
    quint8 m_scheduledEndHour;
    quint8 m_scheduledEndMinute;
    bool m_scheduledEndAM;
    quint8 m_startHour;
    quint8 m_startMinute;
    bool m_startAM;
    quint8 m_endHour;
    quint8 m_endMinute;
    bool m_endAM;

    QString formatTime(quint8 hour, quint8 minute, bool am);
    float computeTimeDifference(quint8 startHour, quint8 startMinute, bool startAM, quint8 endHour, quint8 endMinute, bool endAM);
};

#endif // EMPLOYEESHIFT_H

#include "EmployeeShift.h"

#include <QMetaProperty>
#include <QDebug>

EmployeeShift::EmployeeShift(QObject *parent, quint32 id, QString name, QString note, quint8 scheduledStartHour, quint8 scheduledStartMinute, bool scheduledStartAM, quint8 scheduledEndHour, quint8 scheduledEndMinute, bool scheduledEndAM, quint8 startHour, quint8 startMinute, bool startAM, quint8 endHour, quint8 endMinute, bool endAM) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_note(note), m_scheduledStartHour(scheduledStartHour), m_scheduledStartMinute(scheduledStartMinute), m_scheduledStartAM(scheduledStartAM), m_scheduledEndHour(scheduledEndHour), m_scheduledEndMinute(scheduledEndMinute), m_scheduledEndAM(scheduledEndAM), m_startHour(startHour), m_startMinute(startMinute), m_startAM(startAM), m_endHour(endHour), m_endMinute(endMinute), m_endAM(endAM)
{
}

QStringList EmployeeShift::updatePrefix() {
    return QStringList() << "UpdateEmployeeShift" << QString::number(m_id);
}

quint32 EmployeeShift::id() {
    return m_id;
}

QString EmployeeShift::name() {
    return m_name;
}

QString EmployeeShift::note() {
    return m_note;
}

quint8 EmployeeShift::scheduledStartHour() {
    return m_scheduledStartHour;
}

quint8 EmployeeShift::scheduledStartMinute() {
    return m_scheduledStartMinute;
}

bool EmployeeShift::scheduledStartAM() {
    return m_scheduledStartAM;
}

quint8 EmployeeShift::scheduledEndHour() {
    return m_scheduledEndHour;
}

quint8 EmployeeShift::scheduledEndMinute() {
    return m_scheduledEndMinute;
}

bool EmployeeShift::scheduledEndAM() {
    return m_scheduledEndAM;
}

quint8 EmployeeShift::startHour() {
    return m_startHour;
}

quint8 EmployeeShift::startMinute() {
    return m_startMinute;
}

bool EmployeeShift::startAM() {
    return m_startAM;
}

quint8 EmployeeShift::endHour() {
    return m_endHour;
}

quint8 EmployeeShift::endMinute() {
    return m_endMinute;
}

bool EmployeeShift::endAM() {
    return m_endAM;
}


void EmployeeShift::setName(QString value) {
    if(m_name != value) {
        m_name = value;
        logPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void EmployeeShift::setNote(QString value) {
    if(m_note != value) {
        m_note = value;
        logPropertyChanged(m_note, "note");
        noteChanged(m_note);
    }
}

void EmployeeShift::setScheduledStartHour(quint8 value) {
    if(m_scheduledStartHour != value) {
        m_scheduledStartHour = value;
        logPropertyChanged(m_scheduledStartHour, "scheduledStartHour");
        scheduledStartHourChanged(m_scheduledStartHour);
    }
}

void EmployeeShift::setScheduledStartMinute(quint8 value) {
    if(m_scheduledStartMinute != value) {
        m_scheduledStartMinute = value;
        logPropertyChanged(m_scheduledStartMinute, "scheduledStartMinute");
        scheduledStartMinuteChanged(m_scheduledStartMinute);
    }
}

void EmployeeShift::setScheduledStartAM(bool value) {
    if(m_scheduledStartAM != value) {
        m_scheduledStartAM = value;
        logPropertyChanged(m_scheduledStartAM, "scheduledStartAM");
        scheduledStartAMChanged(m_scheduledStartAM);
    }
}

void EmployeeShift::setScheduledEndHour(quint8 value) {
    if(m_scheduledEndHour != value) {
        m_scheduledEndHour = value;
        logPropertyChanged(m_scheduledEndHour, "scheduledEndHour");
        scheduledEndHourChanged(m_scheduledEndHour);
    }
}

void EmployeeShift::setScheduledEndMinute(quint8 value) {
    if(m_scheduledEndMinute != value) {
        m_scheduledEndMinute = value;
        logPropertyChanged(m_scheduledEndMinute, "scheduledEndMinute");
        scheduledEndMinuteChanged(m_scheduledEndMinute);
    }
}

void EmployeeShift::setScheduledEndAM(bool value) {
    if(m_scheduledEndAM != value) {
        m_scheduledEndAM = value;
        logPropertyChanged(m_scheduledEndAM, "scheduledEndAM");
        scheduledEndAMChanged(m_scheduledEndAM);
    }
}

void EmployeeShift::setStartHour(quint8 value) {
    if(m_startHour != value) {
        m_startHour = value;
        logPropertyChanged(m_startHour, "startHour");
        startHourChanged(m_startHour);
    }
}

void EmployeeShift::setStartMinute(quint8 value) {
    if(m_startMinute != value) {
        m_startMinute = value;
        logPropertyChanged(m_startMinute, "startMinute");
        startMinuteChanged(m_startMinute);
    }
}

void EmployeeShift::setStartAM(bool value) {
    if(m_startAM != value) {
        m_startAM = value;
        logPropertyChanged(m_startAM, "startAM");
        startAMChanged(m_startAM);
    }
}

void EmployeeShift::setEndHour(quint8 value) {
    if(m_endHour != value) {
        m_endHour = value;
        logPropertyChanged(m_endHour, "endHour");
        endHourChanged(m_endHour);
    }
}

void EmployeeShift::setEndMinute(quint8 value) {
    if(m_endMinute != value) {
        m_endMinute = value;
        logPropertyChanged(m_endMinute, "endMinute");
        endMinuteChanged(m_endMinute);
    }
}

void EmployeeShift::setEndAM(bool value) {
    if(m_endAM != value) {
        m_endAM = value;
        logPropertyChanged(m_endAM, "endAM");
        endAMChanged(m_endAM);
    }
}



QString EmployeeShift::scheduledStartFormatted() {
    return formatTime(m_scheduledStartHour, m_scheduledStartMinute, m_scheduledStartAM);
}

QString EmployeeShift::scheduledEndFormatted() {
    return formatTime(m_scheduledEndHour, m_scheduledEndMinute, m_scheduledEndAM);
}

QString EmployeeShift::startFormatted() {
    return formatTime(m_startHour, m_startMinute, m_startAM);
}

QString EmployeeShift::endFormatted() {
    return formatTime(m_endHour, m_endMinute, m_endAM);
}

QString EmployeeShift::formatTime(quint8 hour, quint8 minute, bool am) {
    QString result = (hour < 10 ? "0" : "") + QString::number(hour);
    result += ":";
    result += (minute < 10 ? "0" : "") + QString::number(minute);
    result += am ? "AM" : "PM";
    return result;
}


float EmployeeShift::scheduledHours() {
    return computeTimeDifference(m_scheduledStartHour,
                                 m_scheduledStartMinute,
                                 m_scheduledStartAM,
                                 m_scheduledEndHour,
                                 m_scheduledEndMinute,
                                 m_scheduledEndAM);
}

float EmployeeShift::computeTimeDifference(quint8 startHour, quint8 startMinute, bool startAM, quint8 endHour, quint8 endMinute, bool endAM) {
    if(!startAM) {
        startHour += 12;
    }

    if(!endAM) {
        endHour += 12;
    } else if(endAM && !startAM) {
        endHour += 24;
    }

    float startMinuteFraction = ((float) startMinute) / 60;
    float endMinuteFraction = ((float) endMinute) / 60;

    qDebug() << startMinuteFraction << " : " << endMinuteFraction;

    float start = startHour + startMinuteFraction;
    float end = endHour + endMinuteFraction;

    return end - start;
}






QString EmployeeShift::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << m_note
         << QString::number(m_scheduledStartHour)
         << QString::number(m_scheduledStartMinute)
         << QString::number(m_scheduledStartAM)
         << QString::number(m_scheduledEndHour)
         << QString::number(m_scheduledEndMinute)
         << QString::number(m_scheduledEndAM)
         << QString::number(m_startHour)
         << QString::number(m_startMinute)
         << QString::number(m_startAM)
         << QString::number(m_endHour)
         << QString::number(m_endMinute)
         << QString::number(m_endAM);
    return serializeList(vals);
}

EmployeeShift* EmployeeShift::deserialize(QString serialized, QObject *parent)
{
    QStringList vals = deserializeList(serialized);

    EmployeeShift *obj = new EmployeeShift(parent,
            vals[0].toInt(), vals[1], vals[2],
            vals[3].toInt(),
            vals[4].toInt(),
            vals[5].toInt(),
            vals[6].toInt(),
            vals[7].toInt(),
            vals[8].toInt(),
            vals[9].toInt(),
            vals[10].toInt(),
            vals[11].toInt(),
            vals[12].toInt(),
            vals[13].toInt(),
            vals[14].toInt());

    return obj;
}




#ifndef DLLKIRJASTO_H
#define DLLKIRJASTO_H

#include "Dllkirjasto_global.h"
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QRegularExpression>


class DLLKIRJASTO_EXPORT Dllkirjasto : public QObject
{
Q_OBJECT
public:
    Dllkirjasto(QObject *parent = nullptr);
    void open();

signals:
    void sendNumber(QString);

private:
    QSerialPort *port;

private slots:
    void reserveNumber();
};

#endif // DLLKIRJASTO_H

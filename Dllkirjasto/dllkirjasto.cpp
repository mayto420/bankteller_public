#include "dllkirjasto.h"

Dllkirjasto::Dllkirjasto(QObject *parent) : QObject (parent)
{
    port = new QSerialPort(this);
    connect(port, SIGNAL(readyRead()),
            this, SLOT(reserveNumber()));
}

void Dllkirjasto::open()
{
    QSerialPortInfo desiredPort;
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
        if (port.vendorIdentifier() == 5562 && port.productIdentifier() == 22) {
            desiredPort = port;
            break;
        }
    }

    //  Laitetaan oikeet asetukset, toivottavasti
    //Asetukset on oikeat!
    if (!desiredPort.isNull()) {
        port->setPortName(desiredPort.portName());
        port->setBaudRate(QSerialPort::Baud9600);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);

        if (port->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port" << port->portName() << "opened successfully.";
            //Se toimii ja sanoo sillai

        } else {
            // onkelma alert
            qWarning() << "Failed to open serial port" << port->portName() << "Error:" << port->errorString();
        }
    } else {

        //varmaan tulee näkyyn paljo
        qWarning() << "Desired device not found.";
        delete port; //siivotaan memory
    }
}

void Dllkirjasto::reserveNumber()
{
    QString num = port->readAll();
    qDebug() << "Luettiin numero: " << num;

    num = num.trimmed();
    num = num.remove(QRegularExpression("[\\r\\n\\->]"));

    qDebug() << "uusi numero: " << num;

    emit sendNumber(num);
}


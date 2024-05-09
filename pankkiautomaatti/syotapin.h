#ifndef SYOTAPIN_H
#define SYOTAPIN_H

#include <QDialog>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLineEdit>


namespace Ui {
class syotaPin;
}

class syotaPin : public QDialog
{
    Q_OBJECT

public:
    explicit syotaPin(QWidget *parent = nullptr);
    ~syotaPin();
    //QString getPinKoodi() const;
    void startTimer(); //timerin alustus ja käynnistys

    void setWebToken(const QByteArray &newWebToken);
    void setAccountID(const QString &newAccountID);
public slots:
    void stopTimer(); //ajastimen pysäyttäminen






private:

    Ui::syotaPin *ui;
    QString pinKoodi;
    //QString inputKoodi;

    int attempts = 0;
    QTimer *timer; //QTimer muuttuja ajastinta varten

    void numberClickHandler(); // pin koodia syöttäessä numeronäppäimillä kutsuttava koodi
    void clearTextClickHandler();
    void loginClickHandler();

    QByteArray webToken;
    QString AccountID;


    //Dllkirjasto *kirjasto;





signals:
    void logOut();
    void GoBack(); //palaa päävalikkoon signaali
    void timeout(); //ajastimen päättymisen signaali
    void sendNumberToMainWindow(QString);

private slots:
    void on_GoBackPin_clicked();

    void handleTimeout(); //käsitelee ajastimen päättymisen


};

#endif // SYOTAPIN_H

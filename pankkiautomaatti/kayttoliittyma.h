#ifndef KAYTTOLIITTYMA_H
#define KAYTTOLIITTYMA_H

#include <QDialog>
#include "katsosaldo.h"
#include "nostarahaa.h"
#include "tilitapahtumat.h"
#include "syotapin.h"
#include "mainwindow.h"


#include <QPushButton>
#include <QTimer>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class Kayttoliittyma;
}

class Kayttoliittyma : public QDialog
{
    Q_OBJECT

public:
    explicit Kayttoliittyma(QWidget *parent = nullptr);
    ~Kayttoliittyma();
    void setAccountID(const QString &newAccountID);
    void setWebToken(const QByteArray &newWebToken);



public slots:
    void showKayttoLiittyma();



signals:
    void logOut(); // Signaali kirjaudutaan ulos
    void nosto(); //signaali nostoikkunalle
    void saldo(); //signaali saldoikkunalle
    void tilitapahtumat(); //signaali tilitapahtumaikkunalle



private slots:

    void on_logOut_clicked(); //kirjaudu ulos jäsenfunktio
    void on_nosto_clicked(); //nosto jäsenfunktio
    void on_saldo_clicked(); //saldo jäsenfunktio
    void on_tilitapahtumat_clicked(); //tilitapahtumat jäsenfunktio
    void updateTimer(); //käsitelee ajastimen päättymisen
    void returnToMainWindow(); //paluu pääikkunaan
    void handleTimeoutAgain();
    void stopSecondTimer();








private:
    Ui::Kayttoliittyma *ui;
    Katsosaldo *katsoSaldoDialog;
    NostaRahaa *nostaRahaaDialog;
    TiliTapahtumat *tiliTapahtumatDialog;
    QPushButton *logOutButton;
    QTimer *timer; //QTimer muuttuja ajastinta varten
    QMainWindow *mainWindow;

    QString AccountID;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webToken;



};

#endif // KAYTTOLIITTYMA_H

#include "kayttoliittyma.h"
#include "mainwindow.h"
#include "ui_kayttoliittyma.h"
#include "nostarahaa.h"
#include "katsosaldo.h"
#include "tilitapahtumat.h"
#include "syotapin.h"


#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QNetworkReply>

Kayttoliittyma::Kayttoliittyma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kayttoliittyma),
    katsoSaldoDialog(nullptr),
    nostaRahaaDialog(nullptr),
    tiliTapahtumatDialog(nullptr)

{
    ui->setupUi(this);


    logOutButton = ui->logOut;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Kayttoliittyma::updateTimer);
}

Kayttoliittyma::~Kayttoliittyma()
{
    delete ui;

    delete katsoSaldoDialog;
    delete nostaRahaaDialog;
    delete tiliTapahtumatDialog;
}

void Kayttoliittyma::setAccountID(const QString &newAccountID)
{
    AccountID = newAccountID;
}

void Kayttoliittyma::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void Kayttoliittyma::showKayttoLiittyma()
{
    qDebug() << "näytetään käyttöliittymä";
}


void Kayttoliittyma::on_logOut_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Kirjaudu ulos", "Haluatko varmasti kirjautua ulos?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit logOut(); //Signaali uloskirjautumisesta
        close(); // Suljetaan käyttöliittymäikkuna
    } else {
        // Kirjautumisen peruutus - ilmoita käyttäjälle
        QMessageBox::information(this,"Kirjaudu ulos","Kirjautuminen peruutettu.");
    }
}

void Kayttoliittyma::on_nosto_clicked()
{
    if (!nostaRahaaDialog) {
        nostaRahaaDialog = new NostaRahaa(this);
    }
    nostaRahaaDialog->setAccountID(AccountID);
    nostaRahaaDialog->setWebToken(webToken);
    nostaRahaaDialog->show();
    nostaRahaaDialog->raise();
    nostaRahaaDialog->activateWindow();
}

void Kayttoliittyma::on_saldo_clicked()
{
    if (!katsoSaldoDialog) {
        katsoSaldoDialog = new Katsosaldo(this);
    }
    katsoSaldoDialog->setAccountID(AccountID);
    katsoSaldoDialog->setWebToken(webToken);

    katsoSaldoDialog->showSaldo();
    katsoSaldoDialog->show();
    katsoSaldoDialog->raise();
    katsoSaldoDialog->activateWindow();


}

void Kayttoliittyma::on_tilitapahtumat_clicked()
{
    if (!tiliTapahtumatDialog) {
        tiliTapahtumatDialog = new TiliTapahtumat(this);
    }
    tiliTapahtumatDialog->setAccountID(AccountID);
    tiliTapahtumatDialog->setWebToken(webToken);
    tiliTapahtumatDialog->show();
    tiliTapahtumatDialog->raise();
    tiliTapahtumatDialog->activateWindow();
}




void Kayttoliittyma::updateTimer()
{
    qDebug() << "Toimiiko 2. ajastin?";
    timer->start(30000);
}

void Kayttoliittyma::stopSecondTimer()
{
    timer->stop();
}

void Kayttoliittyma::handleTimeoutAgain()
{
    qDebug() << "ajastimen testaus";
    stopSecondTimer();

    if(MainWindow *mainWindow = MainWindow::getInstance()) {
        mainWindow->showMainWindow();
    } else {
        qDebug() << "Ei palattu";
    }
    close();
}

void Kayttoliittyma::returnToMainWindow()
{
    if (mainWindow) {
        mainWindow->show(); // Näytä pääikkuna
        close(); // Sulje käyttöliittymäikkuna
    }
}


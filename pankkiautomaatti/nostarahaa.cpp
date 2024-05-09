#include "nostarahaa.h"
#include "ui_nostarahaa.h"
#include "kayttoliittyma.h"

NostaRahaa::NostaRahaa(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostaRahaa)
{
    ui->setupUi(this);

    connect(ui->goBack, &QPushButton::clicked, this, &NostaRahaa::returnBack);

    QPushButton *sumButtons[9];
    QStringList buttonNames = {"10", "20", "40", "50", "60", "80", "100", "150", "200"};

    for (int i = 0; i < 9; ++i) {
        sumButtons[i] = this->findChild<QPushButton *>(QString("N%1").arg(buttonNames[i]));
        connect(sumButtons[i], &QPushButton::clicked, this, &NostaRahaa::sumClickHandler);
    }
}

NostaRahaa::~NostaRahaa()
{
    delete ui;
}

void NostaRahaa::returnBack()
{
    this->close();
}

void NostaRahaa::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void NostaRahaa::setAccountID(const QString &newAccountID)
{
    AccountID = newAccountID;
}


void NostaRahaa::updateAccountSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"rahan nosto" << response_data;



    reply->deleteLater();
    putManager->deleteLater();
}
/*

void NostaRahaa::on_btnUpdateBook_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("total","total-amount");

    QString site_url="http://localhost:3000/account";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU*

    putManager = new QNetworkAccessManager(this);
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateAccountSlot(QNetworkReply*)));

    reply = putManager->put(request, QJsonDocument(jsonObj).toJson());

}*/


void NostaRahaa::sumClickHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString sumToText = button->text();
    int summa = sumToText.toInt();
    qDebug() << "Nostetaan : " << summa <<" euroa.";


    QString site_url="http://localhost:3000/account/";
    site_url.append(AccountID);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

      //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    putManager = new QNetworkAccessManager(this);
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateAccountSlot(QNetworkReply*)));

    QJsonObject jsonObj;
    jsonObj.insert("total", -summa);

    reply = putManager->put(request, QJsonDocument(jsonObj).toJson());

}


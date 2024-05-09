#include "katsosaldo.h"
#include "ui_katsosaldo.h"

Katsosaldo::Katsosaldo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Katsosaldo)
{
    ui->setupUi(this);

}

Katsosaldo::~Katsosaldo()
{
    delete ui;
}

void Katsosaldo::setAccountID(const QString &newAccountID)
{
    AccountID = newAccountID;
}


void Katsosaldo::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void Katsosaldo::showSaldo()
{
    QString site_url="http://localhost:3000/account/";
    site_url.append(AccountID);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getAccountsSlot(QNetworkReply*)));

    reply = getManager->get(request); //post
}

void Katsosaldo::on_btnShowSaldo_clicked()
{
    this->close();
}

void Katsosaldo::getAccountsSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString saldo=json_obj["total"].toString();
    ui->label->setText(saldo);
    qDebug()<<saldo;
    reply->deleteLater();
    getManager->deleteLater();
}






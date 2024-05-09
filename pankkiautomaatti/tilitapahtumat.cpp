#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"
#include "mainwindow.h"

TiliTapahtumat::TiliTapahtumat(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TiliTapahtumat)
{
    ui->setupUi(this);
}

TiliTapahtumat::~TiliTapahtumat()
{
    delete ui;
}

void TiliTapahtumat::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void TiliTapahtumat::setAccountID(const QString &newAccountID)
{
    AccountID = newAccountID;
}

void TiliTapahtumat::on_Tili_takaisin_clicked()
{
    this->hide();
    parentWidget()->show();
}

void TiliTapahtumat::on_NaytaTilitapahtumat_btn_clicked()
{
    transactions = new TilitapahtumatLib;
    QString site_url="http://localhost:3000/transaction/";
    site_url.append(AccountID);
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU

    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getTransactionSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void TiliTapahtumat::getTransactionSlot(QNetworkReply *reply)
{


    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    TilitapahtumatLib obj; // Tiedot viedään QListaan oliolistaksi
    transactionList.clear();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();

        obj.setDate(json_obj["transaction_date"].toString()); //listaan viedään päivämäärä
        obj.setAmount(json_obj["amount"].toString()); // ja summa

        // muokattavaa: päivämäärän muotoilu, summan merkki (miinusta vai plussaa)
        // lisäys: total amount tapahtuman jälkeen?
        transactionList.append(obj);
    }

    reply->deleteLater();
    getManager->deleteLater();

    addTransaction();
}


void TiliTapahtumat::addTransaction()
{
    // Luodaan TableModel
    QStandardItemModel *table_model = new QStandardItemModel(transactionList.size(),2); // tähän voisi lisätä kolmannen osan total amount
    // taulukon otsikot:
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Amount"));
    //table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total"));

    for (int row = 0; row < transactionList.size(); ++row) {
        QStandardItem *transactionDate = new QStandardItem(transactionList[row].getDate());
        table_model->setItem(row, 0, transactionDate);
        QStandardItem *transactionAmount = new QStandardItem(transactionList[row].getAmount());
        table_model->setItem(row, 1, transactionAmount);
    }

    ui->tableTransactions->setModel(table_model);
}

#include "kayttoliittyma.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow *MainWindow::instance = nullptr;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    instance = this; // Aseta pääikkunan osoite

    kirjasto = new Dllkirjasto(this);

    connect(kirjasto, SIGNAL(sendNumber(QString)),
                 this, SLOT(pinWindowCreate(QString)));

    kirjasto->open();
    Kayttoliittyma *kayttoliittyma = new Kayttoliittyma(this);
    connect(kayttoliittyma, &Kayttoliittyma::logOut, this, &MainWindow::showMainWindow);
    connect(this, &MainWindow::showMainWindow, kayttoliittyma, &Kayttoliittyma::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

MainWindow* MainWindow::getInstance()
{
    qDebug() << "toimiiko?";
    return instance;
}

void MainWindow::pinWindowCreate(QString num)
{
    qDebug() << "pinWindowCreate: "<< num;
    cardNum = num;
    pinUI= new syotaPin(this);
    connect(pinUI,SIGNAL(sendNumberToMainWindow(QString)),
            this,SLOT(handlePinNumberRead(QString)));
    pinUI->open();
}

void MainWindow::handlePinNumberRead(QString num)
{
    pinKoodi = num;
    qDebug()<<"pinkoodi MW:ssä: "<< pinKoodi;
    doLogIn();
}

void MainWindow::doLogIn()
{
    qDebug()<<"loginissa";


    QJsonObject jsonObj;
    qDebug()<<"jsonObj luotu";
    qDebug() << "pinCardNum: "<< cardNum;
    qDebug() << "pinKoodi: "<< pinKoodi;

    jsonObj.insert("cardNumber", cardNum);
    jsonObj.insert("pin", pinKoodi);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addLogIn(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());


}

void MainWindow::addLogIn(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();

    if(response_data != nullptr){
        Kayttoliittyma* objectKayttoLiittyma = new Kayttoliittyma(this);
        webToken = response_data;

        connect(this, &MainWindow::accountIDRetrieved, objectKayttoLiittyma, &Kayttoliittyma::setAccountID);

        getAccountID();


        objectKayttoLiittyma->setAccountID(AccountID);
        objectKayttoLiittyma->setWebToken(webToken);
        objectKayttoLiittyma->show();
        pinUI->stopTimer();
        pinUI->close();
    }
}

void MainWindow::getAccountID()
{
    QString site_url="http://localhost:3000/card/"+cardNum;
    QNetworkRequest request((site_url));

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(addAccountID(QNetworkReply*)));
    reply = getManager->get(request); //post
}

void MainWindow::addAccountID(QNetworkReply *reply)
{
    response_data=reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    QJsonObject json_obj = json_doc.object();

    AccountID = json_obj["accountID"].toString();

    emit accountIDRetrieved(AccountID);

    reply->deleteLater();
    getManager->deleteLater();
}

void MainWindow::showMainWindow()
{
    qDebug() << "Näytä pääikkuna";
}







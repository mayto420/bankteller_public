#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLineEdit>
#include "dllkirjasto.h"
#include "syotapin.h"
#include "kayttoliittyma.h"
//#include "kayttoliittyma.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QString* cardNumber;
    QSerialPort* tempPtr;

    static MainWindow* getInstance();

    void setWebToken(const QByteArray &newWebToken);
    void setAccountID(const QString &newAccountID);
public slots:
    void showMainWindow();
    void pinWindowCreate(QString);
    void handlePinNumberRead(QString);

signals:
    //void pinRead(bool); // vaihtuu kun luetaan kortti napin sijaan
    void accountIDRetrieved(const QString &AccountID);

private slots:

    void doLogIn();
    void addLogIn(QNetworkReply *reply);
    void getAccountID();
    void addAccountID(QNetworkReply *reply);
private:
    Ui::MainWindow *ui;
    syotaPin *pinUI;
    static MainWindow *instance;
    Dllkirjasto *kirjasto;
    QString pinKoodi;
    QString cardNum;

    QString AccountID;
    QByteArray webToken;

    int loginAttempts = 0;

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;




};

#endif // MAINWINDOW_H

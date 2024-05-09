#ifndef KATSOSALDO_H
#define KATSOSALDO_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Katsosaldo;
}

class Katsosaldo : public QDialog
{
    Q_OBJECT

public:
    explicit Katsosaldo(QWidget *parent = nullptr);

    ~Katsosaldo();
    void setAccountID(const QString &newAccountID);
    void setWebToken(const QByteArray &newWebToken);
    void showSaldo();

private slots:
    void on_btnShowSaldo_clicked();
    void getAccountsSlot(QNetworkReply *reply);

private:
    Ui::Katsosaldo *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString AccountID;
    QByteArray webToken;
};

#endif // KATSOSALDO_H

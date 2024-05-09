#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QStandardItem>


#include "tilitapahtumatlib.h"

namespace Ui {
class TiliTapahtumat;
}

class TiliTapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit TiliTapahtumat(QWidget *parent = nullptr);
    ~TiliTapahtumat();
    void setWebToken(const QByteArray &newWebToken);
    void setAccountID(const QString &newAccountID);

private slots:
    void on_Tili_takaisin_clicked();
    void getTransactionSlot (QNetworkReply *reply);

    void on_NaytaTilitapahtumat_btn_clicked();

private:
    Ui::TiliTapahtumat *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;

    TilitapahtumatLib *transactions;
    QList<TilitapahtumatLib> transactionList;
    void addTransaction();

    QByteArray webToken;
    QString AccountID;
};

#endif // TILITAPAHTUMAT_H

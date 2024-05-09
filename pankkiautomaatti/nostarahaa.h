#ifndef NOSTARAHAA_H
#define NOSTARAHAA_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>



namespace Ui {
class NostaRahaa;
}

class NostaRahaa : public QDialog
{
    Q_OBJECT

public:
    explicit NostaRahaa(QWidget *parent = nullptr);
    ~NostaRahaa();
    void setWebToken(const QByteArray &newWebToken);
    void setAccountID(const QString &newAccountID);


signals:
    void goBack();

private slots:

    void returnBack();

    void updateAccountSlot (QNetworkReply *reply);
    void sumClickHandler();




private:
    Ui::NostaRahaa *ui;
    QNetworkAccessManager *putManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString AccountID;
    QByteArray webToken;


};

#endif // NOSTARAHAA_H

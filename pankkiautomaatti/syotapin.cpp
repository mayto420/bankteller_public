#include "syotapin.h"
#include "ui_syotapin.h"



syotaPin::syotaPin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::syotaPin)
{
    ui->setupUi(this);
    QLineEdit *lineEdit = this->findChild<QLineEdit *>("textPinkoodi");
    if (lineEdit) {
        lineEdit->setReadOnly(true);
    } else {
        qDebug()<< "Ei toimi";
    }
    timer = new QTimer(this);

    startTimer(); //käynnistetään ajastin
    connect(timer, &QTimer::timeout, this, &syotaPin::handleTimeout);
    connect(ui->GoBackPin, &QPushButton::clicked, this, &syotaPin::on_GoBackPin_clicked);

    // Numeronappien luonti ja signaalien kytkentä
    QPushButton *numberButtons[10];
    for (int i = 0; i < 10; ++i) {
        numberButtons[i] = this->findChild<QPushButton *>(QString("N%1").arg(i));
        connect(numberButtons[i], &QPushButton::clicked, this, &syotaPin::numberClickHandler);
    }

    //yhistää clear napin
    connect(ui->clear,&QPushButton::clicked,this, &syotaPin::clearTextClickHandler);

    //yhistää login napin
    connect(ui->logIn,&QPushButton::clicked,this, &syotaPin::loginClickHandler);
}

syotaPin::~syotaPin()
{
    stopTimer();
    delete ui;
}

void syotaPin::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void syotaPin::setAccountID(const QString &newAccountID)
{
    AccountID = newAccountID;
}


void syotaPin::startTimer()
{
    //qDebug() << "Ajastin käynnistyy...";
    timer->start(10000); // Ajastimen käynnistys
}

void syotaPin::stopTimer()
{
    timer->stop(); // Pysäyttää ajastimen
}

void syotaPin::handleTimeout()
{
    // 10 sekuntia ilman toimintaa, palautus pääikkunaan
    qDebug() << "Time's up";

    qDebug() << "Suljetaan pinUI";
    ui->textPinkoodi->clear();
    this->close();
}


void syotaPin::numberClickHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();
    QString currentText = ui->textPinkoodi->text();// pinkoodi tallentuu nappien painalluksella
    pinKoodi = pinKoodi + buttonText;
    ui->textPinkoodi->setText(currentText + "*"); // aina nappia painettaessa tekstiruutuun tulee *
    stopTimer();
    startTimer();
    //qDebug() << "Pin: " << pinKoodi;
}

void syotaPin::clearTextClickHandler()
{
    stopTimer();
    startTimer();
    pinKoodi = "";
    ui->textPinkoodi->clear();
}

void syotaPin::loginClickHandler()
{
    emit sendNumberToMainWindow(pinKoodi);

}




void syotaPin::on_GoBackPin_clicked()
{
    this->close();
}



#include "mainwindow.h"
#include "syotapin.h"

#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QDir>
#include <QFileInfo>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //jos tulee errori että stylesheet puuttuu ja errori mainitsee build kansion
    //silloin kopioit style.qss MYÖS build-kansion sisälle
    QDir dir("");

    QString stylesFolder = dir.absolutePath();
    QString cssFilePath = stylesFolder + "/style.qss";
    qDebug()<<cssFilePath;


    QFile file(cssFilePath);

    if (!file.exists())
    {
        qDebug() << "Stylesheet file not found:" << cssFilePath;
        return -1;
    }

    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    a.setStyleSheet(styleSheet);

    MainWindow w;

    w.show();

    return a.exec();
}


#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QNetworkRequest>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_netManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowTitle("GrowBox Desktop");  // tytul okna

    ui->label_INFO->setText(
        ui->label_INFO->text().arg(VERSION_SW));    // set version in text from variable VERSION_SW

    ui->plainTextEditLog->document()->setMaximumBlockCount(1000);  //max log blockcount size

    logMessage("INFO: Aplikacja uruchomiona.");
    logMessage(QString("Wersja: %1")
                   .arg(VERSION_SW));
    loadSettings();  // wczytaj ustawienia z pliku

}

MainWindow::~MainWindow()
{
    saveSettings();  // zapisz ustawienia do pliku
    delete ui;
}

void MainWindow::on_pushButton_CONNECT_clicked()
{

    const QString ip = ui->lineEdit_IP->text().trimmed();

    if (ip.isEmpty()) {
        QMessageBox::warning(this, "ERROR", "Wprowadz adres IP urzadzenia.");
        logMessage("ERROR: Wprowadz adres IP urzadzenia.");
        return;
    }

    qDebug() << "Connect klikniety, IP =" << ip;
    logMessage(QStringLiteral("Kliknieto POLACZ (IP=%1)").arg(ip));

    // tutaj pozniej zrobimy realne polaczenie HTTP

}

void MainWindow::logMessage(const QString &msg)
{
    // timestamp
    const QString ts =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // dopisz linie do okna logow
    ui->plainTextEditLog->appendPlainText(
        QStringLiteral("[%1] %2").arg(ts, msg));

    // opcjonalnie ogranicz liczbe linii, zeby log nie rosl w nieskonczonosc
    //ui->plainTextEditLog->document()->setMaximumBlockCount(1000);
}



void MainWindow::on_pushButton_CLEAR_LOG_clicked()
{
    ui->plainTextEditLog->clear();
    logMessage("Log wyczyszczony.");
}



// // SETTINGS SAVE AND LOAD

void MainWindow::loadSettings()
{
    // plik settings.cfg w katalogu z .exe
    const QString cfgPath =
        QDir(QCoreApplication::applicationDirPath())
            .filePath("settings.cfg");

    QSettings settings(cfgPath, QSettings::IniFormat);

    // odczyt IP (domyslnie pusty string)
    const QString ip =
        settings.value("network/ip", "192.168.0.220").toString();

    const QString port =
        settings.value("network/port", "8080").toString();

    const bool autoconnect =
        settings.value("network/autoconnect", false).toBool();
    ui->checkBox_AUTOCONNECT->setChecked(autoconnect);

    ui->lineEdit_IP->setText(ip);
    ui->lineEdit_PORT->setText(port);

    logMessage("INFO: Zaladowanie ustawien.");
}

void MainWindow::saveSettings()
{
    const QString cfgPath =
        QDir(QCoreApplication::applicationDirPath())
            .filePath("settings.cfg");

    QSettings settings(cfgPath, QSettings::IniFormat);

    settings.setValue("network/ip",
                      ui->lineEdit_IP->text().trimmed());

    settings.setValue("network/port",
                      ui->lineEdit_PORT->text().trimmed());

    settings.setValue("network/autoconnect",
                      ui->checkBox_AUTOCONNECT->isChecked());

    settings.sync();   // wymus zapis na dysk

    logMessage("INFO: Zapisanie ustawien.");
}

// !! SETTINGS END !!




// NETWORK

void MainWindow::onHttpFinished(QNetworkReply *reply)
{
    // opcjonalnie log / info z odpowiedzi
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "HTTP error:" << reply->errorString();
    } else {
        const QByteArray body = reply->readAll();
        qDebug() << "HTTP OK, response:" << body;
    }

    reply->deleteLater();
}


void MainWindow::on_LED1ON_clicked()
{
    const QString ip   = ui->lineEdit_IP->text().trimmed();
    const QString port = ui->lineEdit_PORT->text().trimmed();

    const QString urlStr = QStringLiteral("http://%1:%2/api/led1on")
                               .arg(ip, port);

    QNetworkRequest req{QUrl(urlStr)};
    m_netManager->get(req);   // HTTP GET
    logMessage("NETWORK: LED 1 ON.");
}

void MainWindow::on_LED1OFF_clicked()
{
    const QString ip   = ui->lineEdit_IP->text().trimmed();
    const QString port = ui->lineEdit_PORT->text().trimmed();

    const QString urlStr = QStringLiteral("http://%1:%2/api/led1off")
                               .arg(ip, port);

    QNetworkRequest req{QUrl(urlStr)};
    m_netManager->get(req);   // HTTP GET
    logMessage("NETWORK: LED 1 OFF.");
}

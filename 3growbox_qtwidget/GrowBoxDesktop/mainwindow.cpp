#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GrowBox Desktop");  // tytul okna

    ui->plainTextEditLog->document()->setMaximumBlockCount(1000);  //max log blockcount size

    logMessage("INFO: Aplikacja wystartowala.");
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
        settings.value("network/ip", "").toString();

    ui->lineEdit_IP->setText(ip);

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

    settings.sync();   // wymus zapis na dysk

    logMessage("INFO: Zapisanie ustawien.");
}

// !! SETTINGS END !!

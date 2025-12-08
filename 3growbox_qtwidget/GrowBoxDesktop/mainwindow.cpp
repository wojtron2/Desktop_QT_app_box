#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_CONNECT_clicked()
{

    const QString ip = ui->lineEdit_IP->text().trimmed();

    if (ip.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Wprowadz adres IP urzadzenia.");
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




#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GrowBox Desktop");  // tytul okna
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
        return;
    }

    qDebug() << "Connect klikniety, IP =" << ip;
    // tutaj pozniej zrobimy realne polaczenie HTTP

}


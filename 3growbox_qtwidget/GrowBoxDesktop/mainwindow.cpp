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

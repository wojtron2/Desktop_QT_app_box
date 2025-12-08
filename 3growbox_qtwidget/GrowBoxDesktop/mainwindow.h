#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void logMessage(const QString &msg);  // deklaracja funkcji logowania

    void on_pushButton_CLEAR_LOG_clicked(); // deklaracja funkcji przycisku czyszczenia logow

private slots:
    void on_pushButton_CONNECT_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

inline constexpr auto VERSION_SW = "0.1.4";


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


private slots:
    void on_pushButton_CONNECT_clicked();

    void on_pushButton_CLEAR_LOG_clicked(); // deklaracja funkcji przycisku czyszczenia logow

private:
    // zapisywanie i odczyt ustawien
    void loadSettings();   // save settings
    void saveSettings();   // load settings


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

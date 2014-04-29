/*
 * This is our main GUI. Everything about the PC side will be handled here.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_TakeReportByLifeGuard_clicked();

    void on_TakeReportBySwimmer_clicked();

    void on_TakeReportByDate_clicked();

    void on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

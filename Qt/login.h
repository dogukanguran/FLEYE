/*
 * With the help of the class we will check authentication of the users.
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    MainWindow *main_;


};

#endif // LOGIN_H

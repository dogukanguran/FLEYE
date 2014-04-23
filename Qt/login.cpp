#include "login.h"
#include "ui_login.h"
#include "database.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    QString uname,password;

    Database db;
    db.openDBConnection();

    uname.append(ui->usernameEdit->text());
    password.append(ui->passwordEdit->text());

    ui->errorText->setText("");
    ui->loginErrorText->setText("");

    if(uname.trimmed().size() == 0 && password.trimmed().size() == 0)
    {
        ui->errorText->setText("Username and Password fields are required to be filled.");
    }
    else if(uname.trimmed().size() == 0)
    {
        ui->errorText->setText("Username field is required to be filled.");
    }
    else if(password.trimmed().size() == 0)
    {
        ui->errorText->setText("Password field is required to be filled.");
    }


    QSqlQuery query;
    query.prepare("SELECT * FROM login WHERE username = :uname AND password = :pass");
    query.bindValue(":uname",uname);
    query.bindValue(":pass",password);
    query.exec();

    if(query.next())
    {
        main = new MainWindow (this);
        main->show();
    }
    else
    {
        ui->loginErrorText->setText("Wrong credentials.");
    }

    /*while(query.next()) {


    }*/
    //db.closeDBConnection();
}


#include "coordination.h"
#include "database.h"
#include "login.h"
#include "ui_login.h"



Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->QWidget::setWindowTitle("Login");

    // first of all, we need to open DB connection
    Database db;
    db.openDBConnection();

}

//desctructor for login class
Login::~Login()
{
    delete ui;
}

//when user clicks connect button
void Login::on_pushButton_clicked()
{
    QString uname,password;

    uname.append(ui->usernameEdit->text());
    password.append(ui->passwordEdit->text());

    ui->errorText->setText("");
    ui->loginErrorText->setText("");
    //if username or password or both of them are empty, give warning.
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

    // if everything is filled, then control the credentials with DB records.
    QSqlQuery query2;
    query2.prepare("SELECT * FROM login WHERE username = :uname AND password = :pass");
    query2.bindValue(":uname",uname);
    query2.bindValue(":pass",password);
    query2.exec();

    if(query2.next())
    {
        main_ = new MainWindow (this);
        main_->QWidget::setWindowTitle("FLEYE Control");
        main_->show();
        this->hide();
    }
    else
    {
        ui->loginErrorText->setText("Wrong credentials.");
    }

    /*while(query.next()) {


    }*/
    //db.closeDBConnection();
}

void Login::setPasswordEditBlank()
{
    ui->passwordEdit->setText("");
}

void Login::setUsernameEditBlank()
{
    ui->usernameEdit->setText("");
}


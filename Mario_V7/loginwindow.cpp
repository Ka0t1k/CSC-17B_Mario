#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow(){
    delete ui;
}

void LoginWindow::on_pushButton_clicked(){

    //Connect to Database
    //createConnection();
    DataB::DBConnect(DBase);
    //Gather Input
    Query uInput;
    uInput.uName=ui->USERNAME->text();
    uInput.pass=ui->PASSWORD->text();

    if(ui->USERNAME->text().isEmpty()){

        QMessageBox::warning(this, "Warning", "You must enter a username to register.");
        return;
    }
    if(ui->PASSWORD->text().isEmpty()){

        QMessageBox::warning(this, "Warning", "You must enter a password to register.");
        return;
    }
    qDebug() << uInput.uName;
    qDebug() << uInput.pass;
    //Try to Register User
    if(DataB::regUsr(uInput,DBase.db)){
        QMessageBox::information(this, "Success"," Registration was successful. You may now login.");
        LoginWindow::reject();
    }
    else{

        //Username Taken
        QMessageBox::warning(this, "Warning", " Username is already taken. Please try again.");
    }
}


//Close window if press cancel button
void LoginWindow::on_pushButton_2_clicked()
{
    LoginWindow::reject();
}

//Set echo mode for password with radio button
void LoginWindow::on_radioButton_clicked(bool checked){
    if(checked){
        ui->PASSWORD->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->PASSWORD->setEchoMode(QLineEdit::Password);
    }
}



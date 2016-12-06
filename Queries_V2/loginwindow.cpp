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
/*
void LoginWindow::connectDatabase()
{
    Connection connection = createConnection();
    if ( !connection.connected ){
        qDebug() << "Not connected!";
        //return 1;
    }
    else{
        qDebug() << "Connected!";
        QSqlQuery query;
        query.exec("SELECT username FROM mario_table");

        while (query.next()) {
            QString name = query.value(0).toString();
            qDebug() << "name:" << name;

        }
        connection.db.close();
        //return 0;
    }

}*/


void LoginWindow::on_pushButton_clicked()
{
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
        QMessageBox::information(this, "Success",
                      " Registration was successful. You may now login.");
    }
    else{
    //Username Taken
        QMessageBox::warning(this, "Warning", " Username is already taken. "
                                              "Please try again.");
    }
}
/*
Connection LoginWindow::createConnection(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("209.129.8.7");
    db.setDatabaseName("48037");
    db.setUserName("48037");
    db.setPassword("48037cis17b");
    Connection connection;
    connection.db = db;
    if (!db.open()) {
        qDebug() << "Database error occurred";
        connection.connected = false;
        return connection;
    }
    connection.connected = true;

    return connection;
}*/


//Close window if press cancel button
void LoginWindow::on_pushButton_2_clicked()
{
    LoginWindow::reject();
}

// Set echo mode for password with radio button
void LoginWindow::on_radioButton_clicked(bool checked){
    if(checked){
        ui->PASSWORD->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->PASSWORD->setEchoMode(QLineEdit::Password);
    }
}




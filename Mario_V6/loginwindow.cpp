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

}


void LoginWindow::on_pushButton_clicked()
{
//Connect to Database
    createConnection();
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
    if(regUsr(uInput)){
        //Then it worked
    }
    else{
        //Then it didnt
    }
}

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
}

//Register User
bool LoginWindow::regUsr(Query Input){
//Check user input against the database
    QString insert;
    QSqlQuery Q(db);
    if(chkUsr(Input)){
    //Define SQL Query
        insert="INSERT INTO mario_table (username,password) VALUES ('"+Input.uName+"', SHA1('"+Input.pass+"'))";
        Q.exec(insert);
        return true;
    }
    else{
        return false;
    }

}
//Check if Users are in Database
bool LoginWindow::chkUsr(Query Input){
    QSqlQuery Q(db);
    QString select;
//Setup a boolean
    bool valid=true;
//Define the Query
    select="SELECT username FROM mario_table WHERE username='"+Input.uName+"'";
    Q.exec(select);
    if(Q.size()==1){
        //Username Taken
        QMessageBox::warning(this, "Warning", " Username is already taken. Please try again.");

        return false;
    }
    else{
        QMessageBox::information(this, "Success", " Registration was successful. You may now login.");
        return valid;
    }

}

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




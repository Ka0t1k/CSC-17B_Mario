#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow(){
    delete ui;
}

struct Connection{
    QSqlDatabase db;
    bool connected;
};

Connection createConnection();

LoginWindow::connectDatabase()
{
    Connection connection = createConnection();
    if ( !connection.connected ){
        qDebug() << "Not connected!";
        return 1;
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

    connectDatabase();

}

Connection createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
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

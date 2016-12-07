#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "database.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog{
    Q_OBJECT
private:
    Connection DBase;

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void connectDatabase();
    //bool regUsr(Query);
    //bool chkUsr(Query);
    Connection createConnection();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_clicked(bool checked);

private:
    Ui::LoginWindow *ui;

};

#endif // LOGINWINDOW_H

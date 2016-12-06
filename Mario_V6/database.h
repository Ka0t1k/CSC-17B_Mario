#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

//Structures
struct Connection{
    QSqlDatabase db;
    bool connected;
};
//SQL Query
struct Query{
    QString uName;
    QString pass;
};
#endif // DATABASE_H

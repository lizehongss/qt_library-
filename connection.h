#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    // 创建图书表
    query.exec("create table library (id varchar primary key, "
                       "name varchar, author varchar)");
    query.exec("insert into library values('6921168509256', 'one', 'li')");
    query.exec("insert into library values('6901285991219', 'two', 'ze')");
    query.exec("insert into library values('6923450656181', 'three', 'hong')");
    return true;
    //创建位置表
    query.exec("create table position (id varchar primary key,"
               "name varchar,author varchar)");

}


#endif // CONNECTION_H

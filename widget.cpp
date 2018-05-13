#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDir>
#include <QList>
#include <QFile>
#include <QtXml>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("library");
    //model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //文件监控
    connect(&myWatcher,&QFileSystemWatcher::fileChanged,
            this,&Widget::showMessage);
    QFile file("F:\\qt_library\\data.txt");
     //QFile  files("//hotstar//scan_date//date.txt");
    if(file.open(QIODevice::WriteOnly)){
        QFileInfo info(file);
        myWatcher.addPath(info.absoluteFilePath());
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_4_clicked()
{
    model->setTable("library");
    model->select();
}
void Widget::showMessage(const QString &path){
    QFile files("F:\\qt_library\\data.txt");
    QStringList lists;
    lists.clear();
    QString nums;

    //读取文件内容
    if (files.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
       QTextStream textStream(&files);
       QRegExp rx("(\\d+)");
       while (!textStream.atEnd())
       {   rx.indexIn(textStream.readLine());
           lists<<rx.cap(1);
       }
        qDebug()<<lists;
        QString id=lists[lists.size()-1];
        qDebug()<<id;
        lists.clear();
        model->setFilter(QString("id='%1'").arg(id));
        if(model->select()){
            for(int i=0;i<model->rowCount();++i){
                QSqlRecord record=model->record(i);
                QString name=record.value("name").toString();
                QString author=record.value("author").toString();
                QSqlQuery query;
                query.prepare("insert into position (id,name,author) values (:id,:name,:author)");
                query.bindValue(":id",id);
                query.bindValue(":name",name);
                query.bindValue(":author",author);
                query.exec();
                while(query.next()){
                    qDebug()<<"ok";
                    qDebug()<<query.value(0);
                }
//                qDebug()<<name;
//                qDebug()<<author;

            }
        }


}
    else    //---打开文件失败
    {

       QMessageBox ::information(NULL, NULL, "open file error");
    }
}

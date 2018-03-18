#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include<QList>
#include<QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("library");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

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

}
    else    //---打开文件失败
    {

       QMessageBox ::information(NULL, NULL, "open file error");
    }
}

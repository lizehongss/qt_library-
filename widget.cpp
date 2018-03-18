#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>


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

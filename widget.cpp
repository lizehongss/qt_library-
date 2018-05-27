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
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //文件监控
    connect(&myWatcher,&QFileSystemWatcher::fileChanged,
            this,&Widget::showMessage);
    //QFile file("F:\\qt_library\\data.txt");
     QFile  files("//hotstar//scan_date//date.txt");
    if(file.open(QIODevice::WriteOnly)){
        QFileInfo info(file);
        myWatcher.addPath(info.absoluteFilePath());
    }
    QDomDocument doc;

    // 添加处理指令即XML说明
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml",
                                                  "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    // 添加根元素
    QDomElement root = doc.createElement("书库");
    doc.appendChild(root);

    // 添加第一个图书元素及其子元素
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;
    id.setValue(QString("6921168509256"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Qt");
    title.appendChild(text);
    text = doc.createTextNode("shiming");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    // 添加第二个图书元素及其子元素
    book = doc.createElement("图书");
    id = doc.createAttribute("编号");
    title = doc.createElement("书名");
    author = doc.createElement("作者");
    id.setValue(QString("6921168509257"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Linux");
    title.appendChild(text);
    text = doc.createTextNode("yafei");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QFile file_xml("my.xml");
    if(!file_xml.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file_xml);

    // 将文档保存到文件，4为子元素缩进字符数
    doc.save(out, 4);
    file_xml.close();

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
    //QFile files("F:\\qt_library\\data.txt");
    QFile  files("//hotstar//scan_date//date.txt");
    QStringList lists;
    lists.clear();
    QString nums;

    //读取文件内容
    if (files.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
       QTextStream textStream(&files);
       QRegExp rx("(\\d+)");
       QString name;
       QString author;
       while (!textStream.atEnd())
       {   rx.indexIn(textStream.readLine());
           lists<<rx.cap(1);
       }
        qDebug()<<lists;
        QString id=lists[lists.size()-1];
        qDebug()<<id;


        QFile file_search("my.xml");
        if (!file_search.open(QIODevice::ReadOnly)) return ;
        QDomDocument doc;
        if (!doc.setContent(&file_search))
        {
            file_search.close();
            return ;
        }
        file_search.close();

        // 以标签名进行查找
        QDomNodeList list = doc.elementsByTagName("图书");
        for(int i=0; i<list.count(); i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute("编号") == id)
            {   // 如果元素的“编号”属性值与我们所查的相同

                    // 如果是查找操作
                    e.attribute("编号");
                    QDomNodeList list = e.childNodes();
                    for(int i=0; i<list.count(); i++)
                    {
                        QDomNode node = list.at(i);
                        if(node.isElement()){
                        if(node.toElement().tagName()=="书名")
                        {name=node.toElement().text();}
                        if(node.toElement().tagName()=="作者")
                        {author=node.toElement().text();}
                    }
                    }

            }
        }
        qDebug()<<name;
        qDebug()<<author;
        int rowNum=model->rowCount();
        model->insertRow(rowNum);
        model->setData(model->index(rowNum,0),id);
        model->setData(model->index(rowNum,1),name);
        model->setData(model->index(rowNum,2),author);
        model->submitAll();
        model->select();
        ui->tableView->setModel(model);

}
    else    //---打开文件失败
    {

       QMessageBox ::information(NULL, NULL, "open file error");
    }
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

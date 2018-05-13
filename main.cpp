#include "widget.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection()) return 1;
    QSqlQuery query;
    Widget w;
    w.show();

    return a.exec();
}

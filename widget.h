#ifndef WIDGET_H
#define WIDGET_H
#include <QFileSystemWatcher>
#include <QWidget>
class QSqlTableModel;
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
    QFileSystemWatch myWatcher;
};

#endif // WIDGET_H

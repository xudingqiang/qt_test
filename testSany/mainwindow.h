#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public:

    QSqlDatabase db ;

    int pageSize = 50 ;
    int offset = 0;



private slots:
    void on_queryButton_clicked();
    void on_pushButton_firstPage_clicked();
    void on_pushButton_prePage_clicked();
    void on_pushButton_nextPage_clicked();
    void on_pushButton_lastPage_clicked();

    void queryData();
};
#endif // MAINWINDOW_H

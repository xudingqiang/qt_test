#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QsqlQueryModel>

#include <QTableView>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QStringList>
#include <QTableWidgetItem>


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

signals:

    void openFileSignal(QString msg);

public slots:
    void openFileWindow();


private slots:
    void on_pushButtonSort_clicked();
    void on_pushButtonInsert_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonQuery_clicked();
    void onTableClicked(const QModelIndex &index);
    void onRowClicked(const QTableWidgetItem &item);

private:

    void createDatabaseFunc();

    void  createTableFunc();

    void queryTableFunc();

    void queryTableDataFunc() ;


    QSqlDatabase sqldb ;//创建QT和数据库的链接

    /*QSqlQueryModel*/ /*sqlmodel*/ ;//存储结果集

    QSqlQueryModel model;

    QSqlQuery *qsqlQuery ;


};
#endif // MAINWINDOW_H

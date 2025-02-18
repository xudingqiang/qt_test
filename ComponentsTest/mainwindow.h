#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include <QString>
#include <QTableWidgetItem>

#include <QTimer>
#include <QTimerEvent>
#include <QPainter>

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


public :

    void timerEvent(QTimerEvent *);

    void paintEvent(QPaintEvent *);

};
#endif // MAINWINDOW_H

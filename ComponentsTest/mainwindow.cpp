#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //新增列
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);


    QList<QString> list ;
    list << "学号" << "姓名"  << "分数";
    ui->tableWidget->setHorizontalHeaderLabels(list);



    QList<QString> listNo ;
    listNo << "01" << "02"  << "03" << "04" << "05";

    QList<QString> listName ;
    listName << "刘国庆" << "张颖"  << "周叶" << "王偲" << "小白";


    QList<QString> listScore ;
    listScore << "88" << "90"  << "77" << "76" << "84";

    for(int i = 0 ; i < 5 ;i ++){
        //新增行
        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(listNo[i]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(listName[i]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(listScore[i]));
    }

    //最后一列自适应宽度
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

   //自适应宽度
  // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //斑马行颜色
    ui->tableWidget->setAlternatingRowColors(true);

        const QString styles = "QTableView\
            {\
                    selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,\
                                                           stop: 0 #616161, stop: 1 505050);\
                    /*alternate-background-color:blue;*/\
            }";

        const QString headerStyle = "QHeaderView::section\
            {\
                    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                                              stop:0 #616161, stop: 0.5 #505050,\
                                              stop: 0.6 #434343, stop:1 #656565);\
                    color: white;\
                    padding-left: 4px;\
                    border: 1px solid #6c6c6c;\
            }\
    ";

    ui->tableWidget->setStyleSheet(styles);
    ui->tableWidget->horizontalHeader()->setStyleSheet(headerStyle);

    QTimer * qTimer = new QTimer(this);
    qTimer->start(500);

    connect(qTimer,&QTimer::timeout,[=](){
        static int num = 1;
        ui->label->setText(QString::number(num++));
    });


    connect(ui->pushButtonStart,&QPushButton::clicked,[=](){
        qTimer->start(500);
    });

    connect(ui->pushButtonFinsih,&QPushButton::clicked,[=](){
        qTimer->stop();
    });


    startTimer(1000);

}


void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    //画笔
    QPen pen (QColor(255,12,12));
    painter.setPen(pen);

    //画刷
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::Dense7Pattern);
    painter.setBrush(brush);

    painter.drawLine(QPoint(0,0),QPoint(100,100));
    painter.drawLine(10,20,120,120);
    painter.drawText(QRect(10,20,200,50),"国庆国庆");
    painter.drawRect(QRect(80,0,200,50));

    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);


    painter.drawEllipse(QRect(300,10,150,50));

    painter.drawEllipse(QPoint(140,40),50,50);



}

void MainWindow:: timerEvent(QTimerEvent*){
    static int num = 1;
    ui->label_2->setText(QString::number(num++));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    createDatabaseFunc();
    ui->setupUi(this);



    // ui->tableView->setEditTriggers();
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    // connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onRowClicked);





    // QList<QString>  header ;
    // header << "学号" << "姓名" << "分数";
    // QHeaderView *qHeaderView  = ui->tableView->horizontalHeader();
    // qHeaderView->headerDataChanged()
    // ui->tableView->setHorizontalHeader(qHeaderView);

    QList<QString>itemsSort ;
    itemsSort << "降序" << "升序";
    ui->comboBoxCond->addItems(itemsSort);


    QList<QString>itemsType ;
    itemsType << "分数" << "学号";
    ui->comboBox->addItems(itemsType);

}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileWindow(){
    qDebug() << "hello this is my slots "  ;
}


void MainWindow::createDatabaseFunc(){
     sqldb =  QSqlDatabase::addDatabase("QSQLITE");
     sqldb.setDatabaseName("TJ.db");
     if(!sqldb.open()) {
         qDebug() << "无法连接到数据库";
         return;
     }else{
         qDebug() << "connect sqlite success ! ";


     }

     // queryTableFunc();
     //createTableFunc();
     queryTableDataFunc();

     // ui->tableView->SelectedClicked
}

void  MainWindow::createTableFunc(){
    qDebug() << "开始点击";
    // QSqlQuery createsql(sqldb) ;
    // QString sql =  QString("create table student(id integer primary key  ,name text not null , score real not null );");

    // bool success = createsql.exec(sql);
    // if(success){
    //       qDebug() << "创建成功";
    // }else{
    //       qDebug() << "创建失败";
    // }

    QSqlQuery query(sqldb);
    QString login = QString("create table login(""user int primary key not null,""password int not null)");
    if(!(query.exec(login)))
    {
        qDebug()<<"数据库表创建失败";
    }
    else
    {
        qDebug()<<"数据库表创建成功";
    }

}

void MainWindow::queryTableFunc(){
    qsqlQuery = new QSqlQuery("TJ");
    QString sql=QString("select * from sany;");
    if(qsqlQuery ->exec(sql)){
        qDebug() << "查询成功";
    }else{
        qDebug() << "查询失败";
    }

}

void MainWindow::queryTableDataFunc(){
   // this->model.setQuery("SELECT * FROM student");
    // ui->tableView->setModel(&model);
    // ui->tableView->show();
}

void MainWindow::on_pushButtonSort_clicked()
{

}



void MainWindow::on_pushButtonInsert_clicked()
{
    QSqlQuery query;

    int id = ui->lineEditId->text().toInt();
    QString name = ui->lineEditName->text();
    double score = ui->lineEditScore->text().toDouble();

    if(id == 0 ){
        QMessageBox::critical(this,"错误","学生的学号不能为0或者空",QMessageBox::Ok);
        return ;
    }

    if(name == ""){
        QMessageBox::critical(this,"错误","学生的姓名不能为空",QMessageBox::Ok);
        return ;
    }

    if(score < 0 || score > 100){
        QMessageBox::critical(this,"错误","请填写有效分数",QMessageBox::Ok);
        return ;
    }

    QString list = QString("insert into student ""values(%1,'%2',%3)").arg(id).arg(name).arg(score);
    if(query.exec(list) == false)
    {
        QMessageBox::critical(this,"错误","数据插入失败!",QMessageBox::Ok);
        return ;
    }
}


void MainWindow::on_pushButtonDelete_clicked()
{
    QSqlQuery query;
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndex currentIndex = selectionModel->currentIndex();


    if (currentIndex.isValid()) {
        int currentRow = currentIndex.row();
        QVariant studentId = ui->tableView->model()->index(currentRow,0).data();

        int id = studentId.toInt();
        qDebug() << "id:  "<<   id;

        QString del = QString("delete from student where id = %1 ").arg(id);
        if(query.exec(del) == false)
        {
            QMessageBox::critical(this,"错误","数据删除失败!",QMessageBox::Ok);
            return ;
        }

    }else{
        QMessageBox::critical(this,"错误","请选择数据!",QMessageBox::Ok);
    }
}


void MainWindow::on_pushButtonUpdate_clicked()
{
    int id = ui->lineEditId->text().toInt();
    QString name = ui->lineEditName->text();
    double score = ui->lineEditScore->text().toDouble();

    if(id == 0 ){
        QMessageBox::critical(this,"错误","学生的学号不能为0或者空",QMessageBox::Ok);
        return ;
    }

    if(name == ""){
        QMessageBox::critical(this,"错误","学生的姓名不能为空",QMessageBox::Ok);
        return ;
    }

    if(score < 0 || score > 100){
        QMessageBox::critical(this,"错误","请填写有效分数",QMessageBox::Ok);
        return ;
    }

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndex currentIndex = selectionModel->currentIndex();


    if (currentIndex.isValid()) {
        int currentRow = currentIndex.row();
        QVariant studentId = ui->tableView->model()->index(currentRow,0).data();

        int id = studentId.toInt();
        qDebug() << "id:  "<<   id;

        QString update = QString("update  student set  name = %1 ,score = %2 where id = %3;").arg(name).arg(score).arg(id);
        QSqlQuery query;
        query.prepare("UPDATE student SET name = :name, score = :score WHERE id = :id");
        query.bindValue(":name", name);
        query.bindValue(":score", score);
        query.bindValue(":id", id);
        if(query.exec() == false)
        {
            QMessageBox::critical(this,"错误","数据修改失败!",QMessageBox::Ok);
            return ;
        }

    }else{
        QMessageBox::critical(this,"错误","请选择数据!",QMessageBox::Ok);
    }

}


void MainWindow::on_pushButtonQuery_clicked()
{
    this->model.setQuery("SELECT * FROM student");
    this->model.setHeaderData(0,Qt::Horizontal, QObject::tr("学号"));
    this->model.setHeaderData(1,Qt::Horizontal, QObject::tr("姓名"));
    this->model.setHeaderData(2,Qt::Horizontal, QObject::tr("分数"));

    // QObject::connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
    //                  [&](const QItemSelection &selected, const QItemSelection &deselected){
    //                      // 当选择变化时，此函数将被调用
    //                      QModelIndexList indexes = selected.indexes();
    //                      if (!indexes.isEmpty()) {
    //                          QModelIndex firstIndex = indexes.first();
    //                          qDebug() << "Row selected:" << firstIndex.row();
    //                      }
    //                  });

    ui->tableView->setModel(&model);
    ui->tableView->show();
}


void MainWindow::onTableClicked(const QModelIndex &index)
{
    qDebug() << "onTableClicked............... ";
    if (index.isValid())
    {
        int selectedRow = index.row();
        QString cellText = index.data().toString();

        // ui->tableView->model()->data(0);
        qDebug() << "cellText:  "<<   cellText << ",rowId:  "<< selectedRow;
    }
}

void MainWindow::onRowClicked(const QTableWidgetItem &index)
{
    // 获取选中的行号
    // int selectedRow = index.row();
    // qDebug() << "selectedRow:  "<<   selectedRow;
}



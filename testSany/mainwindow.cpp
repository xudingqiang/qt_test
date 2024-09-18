#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QSqlDatabase::contains("myConnection")) {
        QSqlDatabase::removeDatabase("myConnection");
    }

    ui->comboBox->setStyleSheet("QComboBox { width: 120px; }");
    ui->comboBoxEdu->setStyleSheet("QComboBox { width: 120px; }");


    ui->comboBoxEdu->addItem("");
    ui->comboBoxEdu->addItem("博士");
    ui->comboBoxEdu->addItem("硕士");
    ui->comboBoxEdu->addItem("本科");
    ui->comboBoxEdu->addItem("大专");
    ui->comboBoxEdu->addItem("中专");


    ui->comboBoxEdu->setCurrentIndex(0);


    ui->comboBox->addItem("");
    for(int k =  31 ;k > 0 ; k--){
        QString text =  QString::number(k);
        qDebug() << "text : " << text ;
        ui->comboBox->addItem(text);
    }
    ui->comboBox->setCurrentIndex(0);


    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #333; color: white;}");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/compatible.db");

    if(!db.open()){
        qDebug() << "无法连接到数据库 !" ;
        qDebug() << "Error opening database:" << db.lastError().text();
        return ;
    }

    qDebug() << "Database connected successfully!";

    ui->tableWidget->setColumnCount(13);

    QStringList headers = {"工号", "userId", "姓名", "性别", "手机号码", "身份证号码", "职级", "入职时间", "毕业院校", "专业", "学历", "邮箱", "职位"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    queryData();

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   // 显示 QTableWidget
    ui->tableWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::queryData(){
    QSqlQuery query;

    query.prepare("SELECT employeeId ,userId ,fullName,gender , phoneNumber , "
                  "idCard ,rank,entryDate ,institution ,major,education ,officeEmail,"
                  "positionName from sany WHERE employeeId like :employeeId AND fullName like :fullName AND rank like :rank AND institution like :institution AND education like :education"
                  " LIMIT :limit OFFSET :offset;");

    QString  employeeId = ui->lineEdit_employeeId->text();
    QString  fullName = ui->lineEdit_fullName->text();
    QString  rank = ui->comboBox->currentText();
    QString  institution = ui->lineEdit_institution->text();
    QString  education = ui->comboBoxEdu->currentText();

    qDebug() << "employeeId: " << employeeId << ", fullName "<< fullName;
     qDebug() << "rank: " << rank << ", institution "<< institution << ", education "<< education;

    // 绑定参数
    query.bindValue(":limit", pageSize);
    query.bindValue(":offset", offset*pageSize);
    query.bindValue(":employeeId", "%"+ui->lineEdit_employeeId->text()+"%");
    query.bindValue(":fullName", "%"+ui->lineEdit_fullName->text()+"%");
    query.bindValue(":rank","%"+rank+"%");
    query.bindValue(":institution", "%"+ui->lineEdit_institution->text()+"%");
    query.bindValue(":education", "%"+education+"%");

    if (!query.exec()) {
        qDebug() << "Error: Failed to insert data." << query.lastError();
    }

    qDebug() << "Database query isSuccess ";

    int row = 0;
    ui->tableWidget->setRowCount(0);

    while (query.next()) {
        QSqlRecord record = query.record();  // 获取记录
        int fieldCount = record.count();     // 获取字段个数

        // QString employeeId = query.value(0).toString();
        // QString userId = query.value(1).toString();
        // QString fullName = query.value(2).toString();
        // QString gender = query.value(3).toString();
        // QString phoneNumber = query.value(4).toString();
        // QString idCard = query.value(5).toString();
        // QString rank = query.value(6).toString();
        // QString entryDate = query.value(7).toString();
        // QString institution = query.value(8).toString();
        // QString major = query.value(9).toString();
        // QString education = query.value(10).toString();
        // QString officeEmail = query.value(11).toString();
        // QString positionName = query.value(12).toString();
        // qDebug() << "fullName:" << fullName << ", phoneNumber:" << phoneNumber << ", rank:" << rank<< ", employeeId:" << employeeId;

        ui->tableWidget->insertRow(row);

        for(int k = 0 ; k <fieldCount ; k++){
            if(k ==  3){
                QString gender = query.value(3).toString();
                if(gender == "1"){
                    ui->tableWidget->setItem(row, k, new QTableWidgetItem("男"));
                }else{
                    ui->tableWidget->setItem(row, k, new QTableWidgetItem("女"));
                }
            }else{
                QString value = query.value(k).toString();
                if(value.contains("?")){
                    value =value.replace("?", "").replace("�","");
                }

                if(value.isNull() || value == "null"){
                    value = "--";
                }
               // qDebug() << "value:" << value  ;
                ui->tableWidget->setItem(row, k, new QTableWidgetItem(value));
            }
        }

        row++;  // 移动到下一行


        // if(fullName.length() == 4 && fullName.contains("?")){
        //     /*qDebug() << "firstName:" << firstName << ", lastName:" << lastName << ", fullName:" << fullName<< ", employeeId:" << employeeId;
        //     qDebug() << fullName.length()  << " ,lastName:  "<< lastName.length();*/
        //     //break;
        //    QSqlQuery updateQuery;
        //    updateQuery.prepare("UPDATE sany SET fullName = :fullName WHERE employeeId = :employeeId");
        //    updateQuery.bindValue(":fullName", firstName+lastName);
        //    updateQuery.bindValue(":employeeId",employeeId);

        //    if (!updateQuery.exec()) {
        //        qDebug() << "Error: Failed to update the full_name field." << query.lastError();
        //    } else {
        //        qDebug() << "Full name updated successfully!";
        //    }
        // }

        // if(fullName.length() > 4){

        // }else{
        //     //update first name
        //     if(fullName.length() > 1){
        //        QString firstChar   = fullName.at(0);
        //         qDebug() << "firstChar:" << firstChar;

        //        QSqlQuery updateQuery;
        //        updateQuery.prepare("UPDATE sany SET firstName = :firstName WHERE employeeId = :employeeId");
        //        updateQuery.bindValue(":firstName", firstChar);
        //        updateQuery.bindValue(":employeeId",employeeId);

        //        if (!updateQuery.exec()) {
        //            qDebug() << "Error: Failed to update the full_name field." << query.lastError();
        //        } else {
        //            qDebug() << "Full name updated successfully!";
        //        }
        //     }

        // }


        //update full where len = 2

        // if(fullName.length() == 2 ){

        //  QString secondCharAsString(fullName.at(1));

        //    QSqlQuery updateQuery;
        //    updateQuery.prepare("UPDATE sany SET lastName = :lastName WHERE employeeId = :employeeId");
        //    updateQuery.bindValue(":lastName", secondCharAsString);
        //    updateQuery.bindValue(":employeeId",employeeId);

        //    if (!updateQuery.exec()) {
        //        qDebug() << "Error: Failed to update the full_name field." << query.lastError();
        //    } else {
        //        qDebug() << "Full name updated successfully!";
        //    }
        // }

    }
}

void MainWindow::on_queryButton_clicked()
{
    queryData();
}


void MainWindow::on_pushButton_firstPage_clicked()
{
    offset = 0 ;
    queryData();
}


void MainWindow::on_pushButton_prePage_clicked()
{
    if(offset > 0){
        offset-- ;
    }
     queryData();
}


void MainWindow::on_pushButton_nextPage_clicked()
{
    offset++ ;
    queryData();
}


void MainWindow::on_pushButton_lastPage_clicked()
{

}


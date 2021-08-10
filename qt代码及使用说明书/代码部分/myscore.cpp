#include "myscore.h"
#include "ui_myscore.h"
#include "global.h"
#include "studentform.h"


myScore::myScore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myScore)
{
    ui->setupUi(this);
    ui->sNo_lineEdit->setText(QString(username_Current));
    ui->sNo_lineEdit->setReadOnly(true);
    ui->Grade_lineEdit->setReadOnly(true);
    ui->classTime_box->addItem("大一上");
    ui->classTime_box->addItem("大一下");
    ui->classTime_box->addItem("大二上");
    ui->classTime_box->addItem("大二下");
}

myScore::~myScore()
{
    delete ui;
}

void myScore::on_pushButton_findcore_back_clicked()
{
    this->hide();
    studentForm *f1 = new studentForm;
    f1->show();
}

void myScore::on_findscoreButton_clicked()
{
    QString classTime = ui->classTime_box->currentText();
    QString sId = ui->sNo_lineEdit->text();
    QString className = ui->className_Edit->text();
    QString teacher = ui->teacher_lineEdit->text();

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select cId from course where object like '%" + className
               + "%' and time = '" + classTime + "' and teacher = '" + teacher + "'");
    if(query.next())
    {
        QString cId = query.value(0).toString();
        //qDebug() << cId;

        query.exec("select score from score where sid = '" + sId + "' and cid = '" + cId + "'");
        if(query.next())
        {
            QString mygrade = query.value(0).toString();
            ui->Grade_lineEdit->setText(mygrade);
        }
        else {
            QMessageBox::warning(this, "无查询结果", "你的该课程没有成绩！");
            ui->Grade_lineEdit->clear();
        }
    }
    else
    {
        QMessageBox::warning(this, "无查询结果", "该课程不存在！");
        ui->Grade_lineEdit->clear();
    }


}

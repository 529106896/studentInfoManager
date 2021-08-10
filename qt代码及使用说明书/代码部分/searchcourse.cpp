#include "searchcourse.h"
#include "ui_searchcourse.h"
#include "global.h"
#include "mycourse.h"
#include <QMessageBox>

searchCourse::searchCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchCourse)
{
    ui->setupUi(this);

    setWindowTitle("Design by 袁佳哲");

    ui->classTimeBox->addItem("大一上");
    ui->classTimeBox->addItem("大一下");
    ui->classTimeBox->addItem("大二上");
    ui->classTimeBox->addItem("大二下");
}

searchCourse::~searchCourse()
{
    delete ui;
}

void searchCourse::on_backButton_clicked()
{
    this->hide();
    mycourse *mc = new mycourse;
    mc->show();
}

void searchCourse::on_clearButton_clicked()
{
    ui->courName_lineEdit->clear();
    ui->courseName_lineEdit->clear();
    ui->teacher_lineEdit->clear();
    ui->classTimeBox->setCurrentIndex(0);
    ui->courseID_lineEdit->clear();
    ui->location_lineEdit->clear();
    ui->credit_lineEdit->clear();
    ui->period_lineEdit->clear();
}

void searchCourse::on_searchButton_clicked()
{

    QString courseName = ui->courName_lineEdit->text();
    QString teacher = ui->teacher_lineEdit->text();
    QString courseTime = ui->classTimeBox->currentText();

    if(courseName.isEmpty() || teacher.isEmpty() || courseName.isEmpty())
    {
        QMessageBox::warning(this, "输入出错", "查找信息不能留空！");
        return;
    }


    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select cId,location,period,credit,object from course where object like "
               "'%" + courseName + "%' and teacher='" + teacher + "' and time='" + courseTime + "'");

    if(query.next())
    {
        QString courseId = query.value(0).toString();
        QString location = query.value(1).toString();
        QString period = query.value(2).toString();
        QString credit = query.value(3).toString();
        QString courseName = query.value(4).toString();

        ui->courseID_lineEdit->setText(courseId);
        ui->courseName_lineEdit->setText(courseName);
        ui->location_lineEdit->setText(location);
        ui->period_lineEdit->setText(period);
        ui->credit_lineEdit->setText(credit);
    }
    else
    {
        QMessageBox::warning(this, "查询无果", "不存在对应教学班！");
    }
}

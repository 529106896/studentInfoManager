#include "addnewcourse.h"
#include "ui_addnewcourse.h"
#include "global.h"
#include <QMessageBox>
#include "coursemanage.h"

addNewCourse::addNewCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addNewCourse)
{
    ui->setupUi(this);
    ui->timeBox->addItem("大一上");
    ui->timeBox->addItem("大一下");
    ui->timeBox->addItem("大二上");
    ui->timeBox->addItem("大二下");
}

addNewCourse::~addNewCourse()
{
    delete ui;
}

void addNewCourse::on_back_button_clicked()
{
    courseManage *cm = new courseManage;
    this->hide();
    cm->show();
}

void addNewCourse::on_submitButton_clicked()
{
    QString cId = ui->courseId_lineEdit->text();
    QString object = ui->object_lineEdit->text();
    QString teacher = ui->teacher_lineEdit->text();
    QString time = ui->timeBox->currentText();
    QString location = ui->location_lineEdit->text();
    QString period = ui->period_lineEdit->text();
    QString credit = ui->credit_lineEdit->text();

    if(cId.isEmpty() || object.isEmpty() || teacher.isEmpty() || time.isEmpty() || location.isEmpty()
            || period.isEmpty() || credit.isEmpty())
    {
        QMessageBox::warning(this, "信息出错", "课程信息不能留空！");
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select cId from course where cId = '" + cId + "'");
    if(query.next())
    {
        QMessageBox::warning(this, "添加出错", "该课程号已存在！");
        return;
    }

    bool isInsertSuccess = query.exec(QString("insert into course values('%0','%1','%2','%3','%4','%5','%6')")
                                      .arg(cId).arg(object).arg(teacher).arg(time).arg(location).arg(period).arg(credit));

    if(isInsertSuccess)
    {
        QMessageBox::information(this, "提示", "添加成功");
    }
    else {
        QMessageBox::warning(this, "添加出错", "请检查填写信息！");
    }
}

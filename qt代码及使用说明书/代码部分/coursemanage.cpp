#include "coursemanage.h"
#include "ui_coursemanage.h"
#include "global.h"
#include "manager.h"
#include <QMessageBox>
#include "allcourseinfo.h"
#include "addnewcourse.h"

courseManage::courseManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::courseManage)
{
    ui->setupUi(this);
    ui->timeBox->addItem("大一上");
    ui->timeBox->addItem("大一下");
    ui->timeBox->addItem("大二上");
    ui->timeBox->addItem("大二下");
    ui->update_button->setDisabled(true);
    ui->delete_button->setDisabled(true);
}

courseManage::~courseManage()
{
    delete ui;
}

void courseManage::on_bakc_button_clicked()
{
    manager * m = new manager;
    this->hide();
    m->show();
}

void courseManage::on_searchButton_clicked()
{
    QString cId = ui->courseId_lineEdit->text();
    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select object, teacher, time, location, period, credit from course where cId = '" + cId + "'");
    if(query.next())
    {
        QString object = query.value(0).toString();
        QString teacher = query.value(1).toString();
        QString time = query.value(2).toString();
        QString location = query.value(3).toString();
        QString period = query.value(4).toString();
        QString credit = query.value(5).toString();

        QString courseNum;

        query.exec("select cId, count(*) from student_course where cId = '" + cId + "' group by '" + cId + "'");

        if(query.next())
            courseNum = query.value(1).toString();
        else {
            courseNum = "0";
        }

        ui->courseName_lineEdit->setText(object);
        ui->teacher_lineEdit->setText(teacher);
        ui->timeBox->setCurrentIndex(ui->timeBox->findText(time));
        ui->location_lineEdit->setText(location);
        ui->period_lineEdit->setText(period);
        ui->credit_lineEdit->setText(credit);
        ui->courseNum_lineEdit->setText(courseNum);

        ui->update_button->setDisabled(false);
        ui->delete_button->setDisabled(false);
    }
    else {
        ui->update_button->setDisabled(true);
        ui->delete_button->setDisabled(true);

        ui->courseName_lineEdit->clear();
        ui->teacher_lineEdit->clear();
        ui->timeBox->setCurrentIndex(0);
        ui->location_lineEdit->clear();
        ui->period_lineEdit->clear();
        ui->credit_lineEdit->clear();
        ui->courseNum_lineEdit->clear();

        QMessageBox::warning(this, "查询无果", "不存在该课程！");

        ui->courseId_lineEdit->setFocus();

    }
}

void courseManage::on_listAllCourse_button_clicked()
{
    this->hide();
    allCourseInfo *aci = new allCourseInfo;
    aci->show();
}

void courseManage::on_add_button_clicked()
{
    addNewCourse *anc = new addNewCourse;
    this->hide();
    anc->show();
}

void courseManage::on_update_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认修改", "确定修改此课程信息？", QMessageBox::Yes|QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        QString cId = ui->courseId_lineEdit->text();
        QString object = ui->courseName_lineEdit->text();
        QString teacher = ui->teacher_lineEdit->text();
        QString time = ui->timeBox->currentText();
        QString location = ui->location_lineEdit->text();
        QString period = ui->period_lineEdit->text();
        QString credit = ui->credit_lineEdit->text();

        bool isUpdateInCourseSuccess = query.exec(QString("update course "
            "set object = '%0',teacher = '%1', time='%2',location='%3',period='%4',credit='%5' where cId = '%6'")
            .arg(object).arg(teacher).arg(time).arg(location).arg(period).arg(credit).arg(cId));

        bool isUpdateInScoreSuccess = query.exec(QString("update score "
            "set object = '%0',teacher = '%1' where cid = '%2'").arg(object).arg(teacher).arg(cId));

        if(isUpdateInScoreSuccess && isUpdateInCourseSuccess)
        {
            QMessageBox::information(this, "提示", "修改成功");

        }
        else {
            QMessageBox::warning(this, "修改失败", "请检查输入信息！");
        }
    }

}

void courseManage::on_delete_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认删除", "确定删除此课程信息？", QMessageBox::Yes|QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        QString cId = ui->courseId_lineEdit->text();

        bool isDeleteSuccess = query.exec("delete from course where cId = '" + cId + "'");

        if(isDeleteSuccess)
        {
            QMessageBox::information(this, "提示", "删除成功");
        }
        else {
            QMessageBox::warning(this, "警告", "删除失败！");
        }
    }
}

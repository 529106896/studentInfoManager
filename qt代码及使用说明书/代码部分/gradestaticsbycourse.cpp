#include "gradestaticsbycourse.h"
#include "ui_gradestaticsbycourse.h"
#include "global.h"
#include "grademanage.h"
#include <QMessageBox>

gradeStaticsByCourse::gradeStaticsByCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeStaticsByCourse)
{
    ui->setupUi(this);
}

gradeStaticsByCourse::~gradeStaticsByCourse()
{
    delete ui;
}

void gradeStaticsByCourse::on_back_button_clicked()
{
    gradeManage *gm = new gradeManage;
    this->hide();
    gm->show();
}

void gradeStaticsByCourse::on_search_button_clicked()
{
    QString cId = ui->cId_lineEdit->text();
    if(cId.isEmpty())
    {
        QMessageBox::warning(this, "统计出错", "课程号不能留空！");
        ui->cName_lineEdit->clear();
        ui->teacher_lineEdit->clear();
        ui->maxScore_lineEdit->clear();
        ui->minScore_lineEdit->clear();
        ui->avgScore_lineEdit->clear();
        ui->selectSum_lineEdit->clear();
        ui->notPassSum_lineEdit->clear();
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select cId from course where cId = '" + cId + "'");
    if(!query.next())
    {
        QMessageBox::warning(this, "统计出错", "该课程不存在！");
        ui->cName_lineEdit->clear();
        ui->teacher_lineEdit->clear();
        ui->maxScore_lineEdit->clear();
        ui->minScore_lineEdit->clear();
        ui->avgScore_lineEdit->clear();
        ui->selectSum_lineEdit->clear();
        ui->notPassSum_lineEdit->clear();
        return;
    }

    query.exec("select object,teacher from course where cId = '" + cId + "'");
    if(query.next())
    {
        QString object = query.value(0).toString();
        QString teacher = query.value(1).toString();
        ui->cName_lineEdit->setText(object);
        ui->teacher_lineEdit->setText(teacher);
    }

    query.exec("select count(sId) from student_course where cId = '" + cId + "'");
    if(query.next())
    {
        QString selectSum = query.value(0).toString();
        ui->selectSum_lineEdit->setText(selectSum);
    }

    query.exec("select max(score.score), min(score.score), avg(score.score) from score where score.cid = '" + cId + "'");

    if(query.next())
    {
        QString maxScore = query.value(0).toString();
        QString minScore = query.value(1).toString();
        QString avgScore = query.value(2).toString();
        ui->maxScore_lineEdit->setText(maxScore);
        ui->minScore_lineEdit->setText(minScore);
        ui->avgScore_lineEdit->setText(avgScore);
    }

    query.exec("select count(*) from score where cid = '" + cId + "' and score.score < 60");

    if(query.next())
    {
        QString notPassSum = query.value(0).toString();
        ui->notPassSum_lineEdit->setText(notPassSum);
    }
}

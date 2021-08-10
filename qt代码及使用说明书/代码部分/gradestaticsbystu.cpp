#include "gradestaticsbystu.h"
#include "ui_gradestaticsbystu.h"
#include "grademanage.h"
#include "global.h"
#include <QMessageBox>

gradeStaticsByStu::gradeStaticsByStu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeStaticsByStu)
{
    ui->setupUi(this);
}

gradeStaticsByStu::~gradeStaticsByStu()
{
    delete ui;
}

void gradeStaticsByStu::on_back_button_clicked()
{
    this->hide();
    gradeManage *gm = new gradeManage;
    gm->show();
}

void gradeStaticsByStu::on_start_button_clicked()
{
    QString sId = ui->sId_lineEdit->text();

    if(sId.isEmpty())
    {
        QMessageBox::warning(this, "统计出错", "学号信息不能为空");
        ui->creditSum_lineEdit->clear();
        ui->avgGrade_lineEdit->clear();
        ui->maxGrade_lineEdit->clear();
        ui->minGrade_lineEdit->clear();
        ui->notpassSum_lineEdit->clear();
        ui->selectedSum_lineEdit->clear();
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select sId from student where sId = '" + sId + "'");

    if(!query.next())
    {
        QMessageBox::warning(this, "统计出错", "该学生不存在！");
        ui->creditSum_lineEdit->clear();
        ui->avgGrade_lineEdit->clear();
        ui->maxGrade_lineEdit->clear();
        ui->minGrade_lineEdit->clear();
        ui->notpassSum_lineEdit->clear();
        ui->selectedSum_lineEdit->clear();
        return;
    }

    query.exec("select sId from student_course where sId = '" + sId + "'");
    if(!query.next())
    {
        QMessageBox::warning(this, "统计出错", "该学生没有选课信息！");
        ui->creditSum_lineEdit->clear();
        ui->avgGrade_lineEdit->clear();
        ui->maxGrade_lineEdit->clear();
        ui->minGrade_lineEdit->clear();
        ui->notpassSum_lineEdit->clear();
        ui->selectedSum_lineEdit->clear();
        return;
    }

    query.exec("select count(cId) from student_course where sId = '" + sId + "'");

    if(query.next())
    {
        QString courseSum = query.value(0).toString();
        ui->selectedSum_lineEdit->setText(courseSum);
    }

    query.exec("select count(*) from score where score < 60 and sid = '" + sId + "'");
    if(query.next())
    {
        QString notPassSum = query.value(0).toString();
        ui->notpassSum_lineEdit->setText(notPassSum);
    }

    query.exec("select max(score) from score where sid = '" + sId + "'");
    if(query.next())
    {
        QString maxScore = query.value(0).toString();
        ui->maxGrade_lineEdit->setText(maxScore);
    }

    query.exec("select min(score) from score where sid = '" + sId + "'");
    if(query.next())
    {
        QString minScore = query.value(0).toString();
        ui->minGrade_lineEdit->setText(minScore);
    }

    query.exec("select avg(score) from score where sid = '" + sId + "'");
    if(query.next())
    {
        QString avgScore = query.value(0).toString();
        ui->avgGrade_lineEdit->setText(avgScore);
    }

    query.exec("select sum(credit) from course where cId in (select cid from score where sid = '" + sId + "' and score > 60)");
    if(query.next())
    {
        QString creditSum = query.value(0).toString();
        ui->creditSum_lineEdit->setText(creditSum);
    }
}

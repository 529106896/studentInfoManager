#include "myinfo.h"
#include "ui_myinfo.h"
#include "global.h"
#include "studentform.h"
#include "resetpwd.h"

myInfo::myInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myInfo)
{
    ui->setupUi(this);

    QString sId = username_Current;

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select sId,name,sex,age,major,class,address,phonenumber from student where sId = '" + sId + "'");

    while(query.next())
    {
        ui->sNo_lineEdit->setText(query.value(0).toString());
        QString name = query.value(1).toString();
        QString sex = query.value(2).toString();
        QString age = query.value(3).toString();
        QString major = query.value(4).toString();
        QString Class = query.value(5).toString();
        QString address = query.value(6).toString();
        QString phone = query.value(7).toString();

        ui->name_lineEdit->setText(name);
        ui->sex_lineEdit->setText(sex);
        ui->age_lineEdit->setText(age);
        ui->major_lineEdit->setText(major);
        ui->address_lineEdit->setText(address);
        ui->phone_lineEdit->setText(phone);
    }
}

myInfo::~myInfo()
{
    delete ui;
}

void myInfo::on_back_button_clicked()
{
    this->hide();
    studentForm *sf = new studentForm;
    sf->show();
}

void myInfo::on_resetPwd_button_clicked()
{
    this->hide();
    resetPwd *rp = new resetPwd;
    rp->show();
}

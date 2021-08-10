#include "studentform.h"
#include "ui_studentform.h"
#include "global.h"
#include "mainwindow.h"
#include "myinfo.h"
#include "myclass.h"
#include "myscore.h"
#include "mycourse.h"

studentForm::studentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentForm)
{
    ui->setupUi(this);
    QLabel *lab = ui->label_user;
    lab->setStyleSheet("color:#0022ff");
    lab->setText("当前用户:" + sName_Current);
    setWindowTitle(QString("Design by 袁佳哲"));
}

studentForm::~studentForm()
{
    delete ui;
}

void studentForm::on_pushButton_clicked()
{
    MainWindow * main;
    this->hide();
    main = new MainWindow;
    main->show();
}

void studentForm::on_pushButton_3_clicked()
{
    this->hide();
    myInfo *mf = new myInfo;
    mf->show();
}

void studentForm::on_stu_findclass_inforButton_clicked()
{
    this->hide();
    myclass * myClass = new myclass;
    myClass->show();

}

void studentForm::on_pushButton_student_findscore_clicked()
{
    this->hide();
    myScore * myscore = new myScore;
    myscore->show();

}

void studentForm::on_stu_find_coursebutton_clicked()
{
    this->hide();
    mycourse * myCourese = new mycourse;
    myCourese->show();
}

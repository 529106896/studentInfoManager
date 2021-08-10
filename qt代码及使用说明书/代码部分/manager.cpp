#include "manager.h"
#include "ui_manager.h"
#include "global.h"
#include "mainwindow.h"
#include "stuinfomanage.h"
#include "classinfomanage.h"
#include "coursemanage.h"
#include "selectcoursemanage.h"
#include "grademanage.h"

manager::manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
    QLabel *lab = ui->label_useradmin;
    lab->setStyleSheet("color:#ff0000");
    lab->setText("当前管理员：" + username_Current);
    setWindowTitle("Design by 袁佳哲");
}

manager::~manager()
{
    delete ui;
}

void manager::on_pushButton_9_clicked()
{
    this->hide();
    MainWindow *mw = new MainWindow;
    mw->show();
}

void manager::on_stu_inform_guanlipushButton_clicked()
{
    this->hide();
    stuinfomanage *sif = new stuinfomanage;
    sif->show();
}

void manager::on_class_managepushButton_clicked()
{
    this->hide();
    classInfoManage *cim = new classInfoManage;
    cim->show();
}

void manager::on_course_manageButton_clicked()
{
    this->hide();
    courseManage *cm = new courseManage;
    cm->show();
}

void manager::on_selectCourse_manageButton_clicked()
{
    selectCourseManage *scm = new selectCourseManage;
    this->hide();
    scm->show();
}

void manager::on_scoremanagepushButton_clicked()
{
    gradeManage *gm = new gradeManage;
    this->hide();
    gm->show();
}

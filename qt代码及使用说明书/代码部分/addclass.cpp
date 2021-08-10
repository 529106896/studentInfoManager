#include "addclass.h"
#include "ui_addclass.h"
#include "global.h"
#include "classinfomanage.h"
#include <QMessageBox>

addClass::addClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addClass)
{
    ui->setupUi(this);
}

addClass::~addClass()
{
    delete ui;
}

void addClass::on_back_button_clicked()
{
    classInfoManage *cim = new classInfoManage;
    this->hide();
    cim->show();
}

void addClass::on_submit_button_clicked()
{
    QString classId = ui->classId_lineEdit->text();
    QString className = ui->className_lineEdit->text();
    QString classMajor = ui->classMajor_lineEdit->text();
    QString classNum = ui->classNum_lineEdit->text();
    QString classMaster = ui->classMaster_lineEdit->text();

    if(classId.isEmpty() || className.isEmpty() || classMajor.isEmpty() || classNum.isEmpty() || classMaster.isEmpty())
    {
        QMessageBox::warning(this, "输入出错", "班级信息不能留空！");
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select classId from class where class = '" + classId + "'");

    if(query.next())
    {
        QMessageBox::warning(this, "添加出错", "该班级号已存在！");
        return;
    }

    bool isInsertSuccess = query.exec(QString("insert into class values('%0','%1','%2','%3','%4')").arg(classId).arg(className).arg(classMajor).arg(classNum).arg(classMaster));

    if(isInsertSuccess)
    {
        QMessageBox::information(this, "提示", "添加成功！");
    }
    else {
        QMessageBox::warning(this, "添加出错", "请检查输入信息！");
    }
}

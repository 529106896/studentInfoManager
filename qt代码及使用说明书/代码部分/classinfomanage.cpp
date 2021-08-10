#include "classinfomanage.h"
#include "ui_classinfomanage.h"
#include <QMessageBox>
#include "global.h"
#include "manager.h"
#include "allclassinfo.h"
#include "addclass.h"

classInfoManage::classInfoManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::classInfoManage)
{
    ui->setupUi(this);
    ui->delete_button->setDisabled(true);
    ui->update_button->setDisabled(true);
}

classInfoManage::~classInfoManage()
{
    delete ui;
}

void classInfoManage::on_back_button_clicked()
{
    this->hide();
    manager *ma = new manager;
    ma->show();
}

void classInfoManage::on_search_button_clicked()
{
    QString classId = ui->classId_lineEdit->text();
    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select className, major, sNum, master from class where classId = '" + classId + "'");
    if(query.next())
    {
        QString className = query.value(0).toString();
        QString major = query.value(1).toString();
        QString sNum = query.value(2).toString();
        QString master = query.value(3).toString();

        ui->className_lineEdit->setText(className);
        ui->classMajor_Edit->setText(major);
        ui->classNum_lineEdit->setText(sNum);
        ui->classMaster_lineEdit->setText(master);

        ui->update_button->setDisabled(false);
        ui->delete_button->setDisabled(false);
    }
    else {
        ui->update_button->setDisabled(true);
        ui->delete_button->setDisabled(true);

        ui->className_lineEdit->clear();
        ui->classMajor_Edit->clear();
        ui->classNum_lineEdit->clear();
        ui->classMaster_lineEdit->clear();

        QMessageBox::warning(this, "查询无果", "不存在该班级！");

        ui->classId_lineEdit->setFocus();

    }

}

void classInfoManage::on_listAll_button_clicked()
{
    this->hide();
    allClassInfo *aci = new allClassInfo;
    aci->show();
}

void classInfoManage::on_add_button_clicked()
{
    this->hide();
    addClass *ac = new addClass;
    ac->show();
}

void classInfoManage::on_update_button_clicked()
{
    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    QString classId = ui->classId_lineEdit->text();
    QString className = ui->className_lineEdit->text();
    QString major = ui->classMajor_Edit->text();
    QString sNum = ui->classNum_lineEdit->text();
    QString master = ui->classMaster_lineEdit->text();

    bool isUpdateSuceess = query.exec(QString("update class set className = '%0', "
                                              "major = '%1', sNum = '%2', "
                                              "master = '%3' where classId = '%4'").arg(className).arg(major).arg(sNum).arg(master).arg(classId));

    if(isUpdateSuceess)
    {
        QMessageBox::information(this, "提示", "更新班级信息成功");
    }
    else {
        QMessageBox::warning(this, "更新失败", "请检查输入信息！");
    }
}

void classInfoManage::on_delete_button_clicked()
{
    QString classId = ui->classId_lineEdit->text();

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认删除", "确定删除此班级信息？", QMessageBox::Yes|QMessageBox::No);

    if(btn == QMessageBox::Yes)
    {
        bool isDeleteSuccess = query.exec("delete from class where classId = '" + classId + "'");
        if(isDeleteSuccess)
        {
            QMessageBox::information(this, "提示", "删除成功");

            ui->classId_lineEdit->clear();
            ui->className_lineEdit->clear();
            ui->classMajor_Edit->clear();
            ui->classNum_lineEdit->clear();
            ui->classMaster_lineEdit->clear();

            ui->classId_lineEdit->setFocus();
        }
        else {
            QMessageBox::warning(this, "警告", "删除失败！");
        }
    }

}

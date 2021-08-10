#include "stuinfomanage.h"
#include "ui_stuinfomanage.h"
#include "global.h"
#include "manager.h"
#include <QMessageBox>
#include "addstuinfo.h"
#include "all_stu_info.h"
#include <QCryptographicHash>

stuinfomanage::stuinfomanage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stuinfomanage)
{
    ui->setupUi(this);
    ui->update_button->setDisabled(true);
    ui->delete_button->setDisabled(true);
    ui->reset_button->setDisabled(true);

    ui->sexBox->addItem("男");
    ui->sexBox->addItem("女");
    ui->statusBox->addItem("正常");
    ui->statusBox->addItem("冻结");

}

stuinfomanage::~stuinfomanage()
{
    delete ui;
}

void stuinfomanage::on_pushButton_7_clicked()
{
    manager *ma = new manager;
    this->hide();
    ma->show();
}

void stuinfomanage::on_pushButton_clicked()
{
    QString sNo = ui->sNo_lineEdit->text();

    if(sNo.isEmpty())
    {
        ui->update_button->setDisabled(true);
        ui->delete_button->setDisabled(true);
        ui->reset_button->setDisabled(true);

        ui->sName_lineEdit->clear();
        ui->sexBox->setCurrentIndex(0);
        ui->age_lineEdit->clear();
        ui->major_lineEdit->clear();
        ui->classId_lineEdit->clear();
        ui->address_lineEdit->clear();
        ui->phone_lineEdit->clear();
        ui->statusBox->setCurrentIndex(0);

        QMessageBox::warning(this, "输入错误", "学号信息不能留空！");

        ui->sNo_lineEdit->setFocus();
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select name,sex,age,major,class,address,phonenumber,status from student where sId = '" + sNo + "'");

    if(query.next())
    {
        QString name = query.value(0).toString();
        QString sex = query.value(1).toString();
        QString age = query.value(2).toString();
        QString major = query.value(3).toString();
        QString Class = query.value(4).toString();
        QString address = query.value(5).toString();
        QString phonenum = query.value(6).toString();
        QString status = query.value(7).toString();

        //qDebug() << status;

        ui->sName_lineEdit->setText(name);
        ui->sexBox->setCurrentIndex(ui->sexBox->findText(sex));
        ui->age_lineEdit->setText(age);
        ui->major_lineEdit->setText(major);
        ui->classId_lineEdit->setText(Class);
        ui->address_lineEdit->setText(address);
        ui->phone_lineEdit->setText(phonenum);
        ui->statusBox->setCurrentIndex(ui->statusBox->findText(status));

        ui->update_button->setDisabled(false);
        ui->delete_button->setDisabled(false);
        ui->reset_button->setDisabled(false);
    }
    else
    {
        ui->update_button->setDisabled(true);
        ui->delete_button->setDisabled(true);
        ui->reset_button->setDisabled(true);

        ui->sName_lineEdit->clear();
        ui->sexBox->setCurrentIndex(0);
        ui->age_lineEdit->clear();
        ui->major_lineEdit->clear();
        ui->classId_lineEdit->clear();
        ui->address_lineEdit->clear();
        ui->phone_lineEdit->clear();
        ui->statusBox->setCurrentIndex(0);

        QMessageBox::warning(this, "查询无果", "该学生不存在");

        ui->sNo_lineEdit->setFocus();


    }
}

void stuinfomanage::on_update_button_clicked()
{
    QString name = ui->sName_lineEdit->text();
    QString sex = ui->sexBox->currentText();
    QString age = ui->age_lineEdit->text();
    QString major = ui->major_lineEdit->text();
    QString Class = ui->classId_lineEdit->text();
    QString address = ui->address_lineEdit->text();
    QString phonenum = ui->phone_lineEdit->text();
    QString sId = ui->sNo_lineEdit->text();
    QString status = ui->statusBox->currentText();

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select classId from class where classId = '" + Class + "'");
    if(query.size() == 0)
    {
        QMessageBox::warning(this, "修改失败", "该班级号不存在！");
        return;
    }

    bool isUpdateSuccess = query.exec(QString("update student set name = '%0', sex = '%1',"
                                      "age = '%2', major = '%3', class = '%4', address = '%5',"
                                      "phonenumber = '%6', status = '%7' where sId = '%8'").arg(name).arg(sex).arg(age).arg(major).arg(Class)
                                      .arg(address).arg(phonenum).arg(status).arg(sId));

    if(isUpdateSuccess)
    {
        //qDebug() << status;
        QMessageBox::information(this, "提示", "修改成功");
    }
    else {
        QMessageBox::warning(this, "提示", "修改失败！请检查输入信息是否有误！");
    }
}

void stuinfomanage::on_addStuInfo_button_clicked()
{
    addStuInfo *asi = new addStuInfo;
    this->hide();
    asi->show();
}

void stuinfomanage::on_listAllStu_button_clicked()
{
    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select sId,name,sex,age,major,class,address,phonenumber,status from student");
    while(query.next())
    {
        QStringList q;
        QString sId = query.value(0).toString();
        QString name = query.value(1).toString();
        QString sex = query.value(2).toString();
        QString age = query.value(3).toString();
        QString major = query.value(4).toString();
        QString classId = query.value(5).toString();
        QString address = query.value(6).toString();
        QString phonenum = query.value(7).toString();
        //QString password = query.value(8).toString();
        QString status = query.value(8).toString();
        q << sId << name << sex << age << major << classId << address << phonenum << status;
        list_all_student.append(q);
    }
    this->hide();
    all_stu_info * all = new all_stu_info;
    all->show();
}

void stuinfomanage::on_delete_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认删除", "确定要删除此学生信息吗？", QMessageBox::Yes|QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        QString sId = ui->sNo_lineEdit->text();

        bool isDeleteSuccess = query.exec("delete from student where sId = '" + sId + "'");

        if(isDeleteSuccess)
        {
            QMessageBox::information(this, "提示", "删除成功");
            ui->sNo_lineEdit->clear();
            ui->sName_lineEdit->clear();
            ui->sexBox->setCurrentIndex(0);
            ui->major_lineEdit->clear();
            ui->classId_lineEdit->clear();
            ui->address_lineEdit->clear();
            ui->phone_lineEdit->clear();
            ui->statusBox->setCurrentIndex(0);

            ui->sNo_lineEdit->setFocus();

            ui->update_button->setDisabled(true);
            ui->delete_button->setDisabled(true);
            ui->reset_button->setDisabled(true);

        }
        else {
            QMessageBox::warning(this, "提示", "删除失败");
        }
    }
}

void stuinfomanage::on_reset_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认重置", "确定要重置此学生密码吗？", QMessageBox::Yes|QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QString sId = ui->sNo_lineEdit->text();
        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        QString originPwd = "123456";
        QString md5_pwd = QCryptographicHash::hash(originPwd.toLatin1(),QCryptographicHash::Md5).toHex();

        bool isResetPwdSuccess = query.exec("update student set password = '" + md5_pwd + "' where sId = '" + sId + "'");
        if(isResetPwdSuccess)
        {
            QMessageBox::information(this, "提示", "已将此学生密码重置为初始密码");
        }
        else {
            QMessageBox::warning(this, "警告", "重置失败！");
        }
    }
}

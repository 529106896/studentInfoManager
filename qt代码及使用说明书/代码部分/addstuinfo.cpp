#include "addstuinfo.h"
#include "ui_addstuinfo.h"
#include "global.h"
#include "stuinfomanage.h"
#include <QMessageBox>

addStuInfo::addStuInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addStuInfo)
{
    ui->setupUi(this);
    ui->sexBox->addItem("男");
    ui->sexBox->addItem("女");
}

addStuInfo::~addStuInfo()
{
    delete ui;
}

void addStuInfo::on_pushButton_3_clicked()
{
    this->hide();
    stuinfomanage *sif = new stuinfomanage;
    sif->show();
}

void addStuInfo::on_clear_button_clicked()
{
    ui->sNo_lineEdit->clear();
    ui->sName_lineEdit->clear();
    ui->sexBox->setCurrentIndex(0);
    ui->age_lineEdit->clear();
    ui->major_lineEdit->clear();
    ui->address_lineEdit->clear();
    ui->classId_lineEdit->clear();
    ui->phonenum_lineEdit->clear();
}

void addStuInfo::on_submit_button_clicked()
{
    QString sNo = ui->sNo_lineEdit->text();
    QString name = ui->sName_lineEdit->text();
    QString sex = ui->sexBox->currentText();
    QString age = ui->age_lineEdit->text();
    QString major = ui->major_lineEdit->text();
    QString address = ui->address_lineEdit->text();
    QString Class = ui->classId_lineEdit->text();
    QString phone = ui->phonenum_lineEdit->text();

    if(sNo.isEmpty() || name.isEmpty() || age.isEmpty() || major.isEmpty() ||
            address.isEmpty() || Class.isEmpty() || phone.isEmpty())
    {
        QMessageBox::warning(this, "警告", "输入信息不能留空！");
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select sId from student where sId = '" + sNo + "'");

    if(query.next())
    {
        QMessageBox::warning(this, "新增出错", "该学号已经存在！");
        return;
    }

    query.exec("select classId from class where classId = '" + Class + "'");
    if(query.size() == 0)
    {
        QMessageBox::warning(this, "新增出错", "该班级号不存在！");
        return;
    }

    bool isInsertSuccess = query.exec(QString("insert into student values('%0','%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(sNo).arg(name)
               .arg(sex).arg(age).arg(major).arg(Class).arg(address).arg(phone).arg("123456").arg("正常"));

    if(isInsertSuccess)
        QMessageBox::information(this, "提示", "新增学生成功！");
    else {
        QMessageBox::warning(this, "新增失败", "请检查输入信息是否有误");
    }

}

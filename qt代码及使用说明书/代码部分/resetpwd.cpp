#include "resetpwd.h"
#include "ui_resetpwd.h"
#include "global.h"
#include "myinfo.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QCryptographicHash>

resetPwd::resetPwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resetPwd)
{
    ui->setupUi(this);
    ui->submit_button->setDisabled(true);
    ui->error_label->clear();
    ui->error_label->setStyleSheet("color:#ff0000");
}

resetPwd::~resetPwd()
{
    delete ui;
}


void resetPwd::on_back_button_clicked()
{
    this->hide();
    myInfo *mf = new myInfo;
    mf->show();
}

void resetPwd::on_oldPwd_lineEdit_textChanged(const QString &arg1)
{
    QString oldPwd = arg1;

    if(oldPwd.compare(pwd_Current) != 0)
    {
        ui->error_label->setText("原密码输入错误！");
        ui->submit_button->setDisabled(true);
    }
    else {
        ui->error_label->clear();
    }
}

void resetPwd::on_newPwd_lineEdit_textChanged(const QString &arg1)
{
    QString newPwd = arg1;
    //qDebug() << arg1 << pwd_Current;
    if(newPwd.compare(pwd_Current) == 0)
    {
        ui->error_label->setText("不可与原密码一致！");
        ui->submit_button->setDisabled(true);
    }
    else {
        ui->error_label->clear();
    }
}

void resetPwd::on_repeatPwd_lineEdit_textChanged(const QString &arg1)
{
    QString repeatedPwd = arg1;
    QString newPwd = ui->newPwd_lineEdit->text();
    if(repeatedPwd.compare(newPwd) != 0)
    {
        ui->error_label->setText("两次密码输入不一致！");
        ui->submit_button->setDisabled(true);

    }
    else {
        ui->error_label->clear();
        ui->submit_button->setDisabled(false);
    }
}

void resetPwd::on_submit_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "确认提交", "确定要修改个人密码吗？", QMessageBox::Yes|QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QSqlDatabase db;
        connect_to_database(db);

        QSqlQuery query(db);

        QString sId = username_Current;
        //QString newPwd = ui->newPwd_lineEdit->text();
        QString newPwd = QCryptographicHash::hash(ui->newPwd_lineEdit->text().toLatin1(), QCryptographicHash::Md5).toHex();

        bool isResetPwdSuccess = query.exec("update student set password = '" + newPwd + "' where sId = '" + sId + "'");

        if(isResetPwdSuccess)
        {
            QMessageBox::information(this, "提示", "修改成功！请重新登录！", QMessageBox::Yes);
            this->hide();
            MainWindow *mw = new MainWindow;
            mw->show();
        }
        else {
            QMessageBox::warning(this, "修改失败", "请检查密码格式！");
        }
    }
}

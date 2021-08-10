#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QMouseEvent>
#include <QtDebug>
#include <global.h>
#include <QCryptographicHash>
//#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Login_password->setEchoMode(QLineEdit::Password);
    ui->Login_username->setPlaceholderText("请输入学号或管理员账号");
    ui->Login_password->setPlaceholderText("请输入密码");
    ui->studentButton->setChecked(true);

    loginFailTimes = 0;

    ui->captcha_lineEdit->setVisible(false);
    ui->captcha_Label->setVisible(false);
    ui->loginFailTimes_Label->setVisible(false);
    ui->loginFailTimes_Label->setStyleSheet("color:#ff0000");

    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());

    captcha = getCaptcha();
    color = getColor();

    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer.start(500);

}

MainWindow::~MainWindow()
{
    delete ui;
    //timer.stop();
}

void MainWindow::onTimeOut()
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    color = getColor();
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *evt)
{
    if(QRect(300, 190, 84, 24).contains(evt->pos()))
    {
        captcha = getCaptcha();
        repaint();
    }
}

void MainWindow::paintEvent(QPaintEvent *evt)
{

    if(loginFailTimes >= 3)
    {
        QPainter painter(this);

        painter.fillRect(300, 190, 84, 24, Qt::lightGray);

        painter.setFont(QFont("Comic Sans MS"));

        for(int i = 0; i < 4; i++)
        {
            painter.setPen(color[i]);
            painter.drawText(300 + 20 * i, 190, 20, 24, Qt::AlignCenter, QString(captcha[i]));
        }

        for(int i = 0; i < 100; i++)
        {
            painter.setPen(color[i % 4]);
            painter.drawPoint(300 + qrand()%83, 190 + qrand() % 23);
        }
    }
}

QString MainWindow::getCaptcha()
{
    QString ret = "";

    for(int i = 0; i < 4; i++)
    {
        int c = (qrand() % 2)? 'a' : 'A';
        ret += static_cast<QChar>(c + qrand() % 26);
    }

    return ret;
}

Qt::GlobalColor* MainWindow::getColor()
{
    static Qt::GlobalColor colors[4];

    for(int i = 0; i < 4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>((qrand() % 16) + 2);
    }

    return colors;
}

void MainWindow::on_LoginButton_clicked()
{
    QString input_userName = ui->Login_username->text();
    //QString input_password = ui->Login_password->text();
    QString input_password = QCryptographicHash::hash(ui->Login_password->text().toLatin1(), QCryptographicHash::Md5).toHex();
    QString input_captcha = ui->captcha_lineEdit->text();

    if(loginFailTimes >= 3)
    {
//        qDebug() << captcha;
//        qDebug() << input_captcha;
        if(input_captcha.compare(captcha) != 0)
        {
            QMessageBox::warning(this, "登录失败", "验证码错误！");
            return;
        }
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    if(ui->adminButton->isChecked())
    {

        query.exec("select adminName from admin where adminName = '" + input_userName + "'");

        if(!query.next())
        {
            QMessageBox::warning(this, "登录失败", "该用户不存在！");
            return;
        }

        query.exec("select aid, adminName, password from admin where adminName = '" + input_userName + "' and password = '" + input_password + "'");

        bool isLoginSuccess = false;

        if(query.next())
        {
            QString userName = query.value(1).toString();
            QString pwd = query.value(2).toString();
            username_Current = userName;
            pwd_Current = ui->Login_password->text();
            isLoginSuccess = true;
            //QString md5_pwd = QCryptographicHash::hash(pwd.toLatin1(), QCryptographicHash::Md5).toHex();
            this->hide();
            m = new manager;
            m->show();
        }

        if(!isLoginSuccess)
        {
            QMessageBox::warning(this, "登录失败", "密码错误！");
            ui->Login_username->setFocus();
        }
    }

    if(ui->studentButton->isChecked())
    {
        query.exec("select sId from student where sId = '" + input_userName + "'");

        if(!query.next())
        {
            QMessageBox::warning(this, "登录失败", "该用户不存在！");
            return;
        }

        query.exec("select status from student where sId = '" + input_userName + "'");
        if(query.next())
        {
            QString status = query.value(0).toString();
            if(status.compare("冻结") == 0)
            {
                QMessageBox::warning(this, "登录失败", "该用户已被冻结\n请联系管理员进行解冻！");
                return;
            }
        }

        bool isLoginSuccess = false;

        query.exec("select sId, name, password from student where sId = '" + input_userName + "' and password = '" + input_password + "'");

        if(query.next())
        {
            QString sNo = query.value(0).toString();
            QString sName = query.value(1).toString();
            QString pwd = query.value(2).toString();
            //qDebug() << sNo << sName << pwd;
            username_Current = sNo;
            pwd_Current = ui->Login_password->text();
            sName_Current = sName;
            isLoginSuccess = true;
            //qDebug() << "学生" + sName + "登录成功";
            this->hide();
            f = new studentForm;
            f->show();
        }

        if(!isLoginSuccess)
        {
            QMessageBox::warning(this, "警告", "密码错误！");
            loginFailTimes++;
            ui->Login_username->setFocus();
            ui->loginFailTimes_Label->setVisible(true);
            ui->loginFailTimes_Label->setText(QString("登录失败次数：%0 次").arg(loginFailTimes));
        }
    }

    if(loginFailTimes >= 3)
    {
        ui->captcha_Label->setVisible(true);
        ui->captcha_lineEdit->setVisible(true);
        ui->adminButton->move(133, 230);
        ui->studentButton->move(290, 230);
        ui->LoginButton->move(130, 280);
        ui->clearButton->move(290, 280);
    }

    if(loginFailTimes >= 5 && ui->studentButton->isChecked())
    {
        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        QString username = ui->Login_username->text();

        query.exec("update student set status = '冻结' where sId = '" + username + "'");

        ui->LoginButton->setDisabled(true);
        ui->clearButton->setDisabled(true);

        QMessageBox::warning(this, "登录失败", "登录失败次数过多\n您的账户已被冻结！\n请联系管理员进行解冻");

    }

}

void MainWindow::on_clearButton_clicked()
{
    ui->Login_username->clear();
    ui->Login_password->clear();
    ui->captcha_lineEdit->clear();
}

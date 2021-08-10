#include "myclass.h"
#include "ui_myclass.h"
#include <mainwindow.h>
#include "studentform.h"
#include "global.h"
#include <QSqlDatabase>

myclass::myclass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myclass)
{
    ui->setupUi(this);
    setWindowTitle(QString("Design by 袁佳哲"));

    QSqlDatabase db;
    connect_to_database(db);

    QString uid = username_Current;
    QString myClass = "";
    QSqlQuery query(db);

    query.exec("select class from student where sId = "+ uid);

    if(query.next())
    {
        myClass = query.value(0).toString();
    }

    query.exec("select classId, className, major, sNum, master from class where classId = " + myClass);

    if(query.next())
    {
        QString cId = query.value(0).toString();
        QString cName = query.value(1).toString();
        QString cMajor = query.value(2).toString();
        QString cNum = query.value(3).toString();
        QString cMaster = query.value(4).toString();

        ui->classId_lineEdit->setText(cId);
        ui->className_lineEdit->setText(cName);
        ui->classMajor_lineEdit->setText(cMajor);
        ui->classNum_lineEdit->setText(cNum);
        ui->classMaster_lineEdit->setText(cMaster);
    }

}

myclass::~myclass()
{
    delete ui;
}

void myclass::on_backButton_clicked()
{
    this->hide();
    studentForm * f2 = new studentForm;
    f2->show();
}

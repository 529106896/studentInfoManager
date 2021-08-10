#include "allcourseinfo.h"
#include "ui_allcourseinfo.h"
#include "global.h"
#include "coursemanage.h"
#include "exporttable.h"

allCourseInfo::allCourseInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::allCourseInfo)
{
    ui->setupUi(this);

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select cId,object,teacher,time,location,period,credit from course");

    while(query.next())
    {
        QString cId = query.value(0).toString();
        QString object = query.value(1).toString();
        QString teacher = query.value(2).toString();
        QString time = query.value(3).toString();
        QString location = query.value(4).toString();
        QString period = query.value(5).toString();
        QString credit = query.value(6).toString();

        QString courseNum;

        QSqlQuery query1(db);

        query1.exec("select cId, count(*) from student_course where cId = '" + cId + "' group by '" + cId + "'");

        if(query1.next())
            courseNum = query1.value(1).toString();
        else {
            courseNum = "0";
        }

        QStringList q;
        q << cId << object << teacher << time << location << period << credit << courseNum;

        int rowCount = ui->courseIInfoTable->rowCount();
        ui->courseIInfoTable->insertRow(rowCount);

        for(int i = 0; i<q.size(); i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(q.at(i));
            ui->courseIInfoTable->setItem(rowCount, i, item);
        }
    }

    int columnCount = ui->courseIInfoTable->columnCount();
    int rowCount = ui->courseIInfoTable->rowCount();

    for(int i = 0; i <columnCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            ui->courseIInfoTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

allCourseInfo::~allCourseInfo()
{
    delete ui;
}

void allCourseInfo::on_back_button_clicked()
{
    this->hide();
    courseManage *cm = new courseManage;
    cm->show();
}

void allCourseInfo::on_export_button_clicked()
{
    Table2Excel(ui->courseIInfoTable, "所有课程信息");
}

#include "mycourse.h"
#include "ui_mycourse.h"
#include "studentform.h"
#include "global.h"
#include "searchcourse.h"
#include "exporttable.h"

mycourse::mycourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mycourse)
{
    ui->setupUi(this);
    QString sId = username_Current;

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    QStringList myCourseIdList;

    query.exec("select cId from student_course where sId = '" + sId + "'");

    while(query.next())
    {
        QString getCId = query.value(0).toString();

        //qDebug() << getCId;

        myCourseIdList << getCId;
    }

    QVariantList myCourseList;

    for(auto i : myCourseIdList)
    {
//        qDebug() << i;
        query.exec("select cId, object, teacher, time, location, period, credit from course where cId = '" + i + "'");
        while(query.next())
        {
            QString courseId = query.value(0).toString();
            QString object = query.value(1).toString();
            QString teacher = query.value(2).toString();
            QString time = query.value(3).toString();
            QString location = query.value(4).toString();
            QString period = query.value(5).toString();
            QString credit = query.value(6).toString();
            QStringList q;
            q << courseId << object << teacher << time << location << period << credit;
            myCourseList.append(q);
        }
    }

    for(auto i : myCourseList)
    {
        int rowCount = ui->myCourseTable->rowCount();

        ui->myCourseTable->insertRow(rowCount);

        QStringList rowData = i.toStringList();

        for (int j = 0; j < rowData.size(); j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(rowData.at(j));
            ui->myCourseTable->setItem(rowCount, j, item);
        }
    }

    int columnCount = ui->myCourseTable->columnCount();
    int rowCount = ui->myCourseTable->rowCount();

    for(int i = 0; i <columnCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            ui->myCourseTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }


}

mycourse::~mycourse()
{
    delete ui;
}

void mycourse::on_pushButton_2_clicked()
{
    this->hide();
    studentForm *f1 = new studentForm;
    f1->show();
}

void mycourse::on_searchButton_clicked()
{
    this->hide();
    searchCourse *sc = new searchCourse;
    sc->show();
}

void mycourse::on_export_button_clicked()
{
    Table2Excel(ui->myCourseTable, "我的课程信息");
}

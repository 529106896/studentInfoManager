#include "allclassinfo.h"
#include "ui_allclassinfo.h"
#include "global.h"
#include "classinfomanage.h"
#include "exporttable.h"

allClassInfo::allClassInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::allClassInfo)
{
    ui->setupUi(this);

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select classId,className,major,sNum,master from class");

    while(query.next())
    {
        QString classId = query.value(0).toString();
        QString className = query.value(1).toString();
        QString major = query.value(2).toString();
        QString sNum = query.value(3).toString();
        QString master =query.value(4).toString();

        QStringList q;
        q << classId << className << major << sNum << master;

        int rowCount = ui->classInfoTable->rowCount();
        ui->classInfoTable->insertRow(rowCount);

        for(int i = 0; i<q.size(); i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(q.at(i));
            ui->classInfoTable->setItem(rowCount, i, item);
        }
    }

    int columnCount = ui->classInfoTable->columnCount();
    int rowCount = ui->classInfoTable->rowCount();

    for(int i = 0; i <columnCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            ui->classInfoTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

allClassInfo::~allClassInfo()
{
    delete ui;
}

void allClassInfo::on_back_button_clicked()
{
    this->hide();
    classInfoManage *cim = new classInfoManage;
    cim->show();
}

void allClassInfo::on_export_button_clicked()
{
    Table2Excel(ui->classInfoTable, "所有班级信息");
}

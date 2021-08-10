#include "all_stu_info.h"
#include "ui_all_stu_info.h"
#include "stuinfomanage.h"
#include "exporttable.h"

all_stu_info::all_stu_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::all_stu_info)
{
    ui->setupUi(this);
    setWindowTitle(QString("Design by 袁佳哲"));


    for(auto i : list_all_student)
    {
        int rowCount = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(rowCount);

        QStringList rowData = i.toStringList();

        for (int j = 0; j < rowData.size(); j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(rowData.at(j));
            ui->tableWidget->setItem(rowCount, j, item);
        }
    }

    int columnCount = ui->tableWidget->columnCount();
    int rowCount = ui->tableWidget->rowCount();

    for(int i = 0; i <columnCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            ui->tableWidget->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

all_stu_info::~all_stu_info()
{
    delete ui;
}

void all_stu_info::on_back_stuButton_clicked()
{
    this->hide();
    list_all_student.clear();
    ui->tableWidget->clear();
    stuinfomanage *sfm = new stuinfomanage;
    sfm->show();
}

void all_stu_info::on_export_button_clicked()
{
    Table2Excel(ui->tableWidget, "所有学生信息");
}

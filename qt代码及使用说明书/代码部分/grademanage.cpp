#include "grademanage.h"
#include "ui_grademanage.h"
#include "manager.h"
#include "global.h"
#include <QMessageBox>
#include "addnewgrade.h"
#include <QInputDialog>
#include "gradestaticsbystu.h"
#include "gradestaticsbycourse.h"
#include "exporttable.h"

gradeManage::gradeManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeManage)
{
    ui->setupUi(this);
    ui->gradeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->currentSelected_label->setVisible(false);
    ui->update_gradeButton->setDisabled(true);
    ui->delete_button->setDisabled(true);
    updataTable();
}

gradeManage::~gradeManage()
{
    delete ui;
}

void gradeManage::updataTable()
{
    ui->gradeTable->clearContents();
    ui->gradeTable->setRowCount(0);

    QSqlDatabase db;
    connect_to_database(db);

    QSqlQuery query(db);

    query.exec("select sid,cid,object,score,teacher from score order by sid");

    while(query.next())
    {
        QString sId = query.value(0).toString();
        QString cId = query.value(1).toString();
        QString object = query.value(2).toString();
        QString score = query.value(3).toString();
        QString teacher = query.value(4).toString();

        QStringList q;
        q << sId << cId << object << score << teacher;

        int rowCount = ui->gradeTable->rowCount();
        ui->gradeTable->insertRow(rowCount);

        for(int i = 0; i<q.size(); i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(q.at(i));
            ui->gradeTable->setItem(rowCount, i, item);
        }
    }

    int columnCount = ui->gradeTable->columnCount();
    int rowCount = ui->gradeTable->rowCount();

    for(int i = 0; i <columnCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            ui->gradeTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

void gradeManage::on_back_button_clicked()
{
    manager *m = new manager;
    this->hide();
    m->show();
}

void gradeManage::on_listAll_button_clicked()
{
    updataTable();
    ui->currentSelected_label->setVisible(false);
    ui->update_gradeButton->setDisabled(true);
    ui->delete_button->setDisabled(true);
//    ui->sId_lineEdit->clear();
//    ui->cId_lineEdit->clear();
}

void gradeManage::on_searchBysNo_clicked()
{
    ui->gradeTable->clearContents();
    ui->gradeTable->setRowCount(0);

    ui->currentSelected_label->setVisible(false);
    ui->update_gradeButton->setDisabled(true);
    ui->delete_button->setDisabled(true);
//    ui->sId_lineEdit->clear();
//    ui->cId_lineEdit->clear();

    QString sId = ui->sId_lineEdit->text();
    //QString cId = ui->cId_lineEdit->text();

    if(sId.isEmpty())
    {
        QMessageBox::warning(this, "????????????", "?????????????????????");
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select sId from student where sId = '" + sId + "'");

    if(!query.next())
    {
        QMessageBox::warning(this, "????????????", "?????????????????????");
        return;
    }

    query.exec("select sid,cid,object,score,teacher from score where sid = '" + sId + "' order by cid");

    if(query.size() != 0)
    {

        while(query.next())
        {
            QString sId = query.value(0).toString();
            QString cId = query.value(1).toString();
            QString object = query.value(2).toString();
            QString score = query.value(3).toString();
            QString teacher = query.value(4).toString();

            QStringList q;
            q << sId << cId << object << score << teacher;

            int rowCount = ui->gradeTable->rowCount();
            ui->gradeTable->insertRow(rowCount);

            for(int i = 0; i<q.size(); i++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(q.at(i));
                ui->gradeTable->setItem(rowCount, i, item);
            }
        }

        int columnCount = ui->gradeTable->columnCount();
        int rowCount = ui->gradeTable->rowCount();

        for(int i = 0; i <columnCount; i++)
        {
            for(int j = 0; j < rowCount; j++)
            {
                ui->gradeTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
    }
    else {
        QMessageBox::warning(this, "????????????", "??????????????????????????????");
    }

}

void gradeManage::on_searchBycId_clicked()
{
    ui->gradeTable->clearContents();
    ui->gradeTable->setRowCount(0);

    ui->currentSelected_label->setVisible(false);
    ui->update_gradeButton->setDisabled(true);
    ui->delete_button->setDisabled(true);
//    ui->sId_lineEdit->clear();
//    ui->cId_lineEdit->clear();

    //QString sId = ui->sId_lineEdit->text();
    QString cId = ui->cId_lineEdit->text();

    if(cId.isEmpty())
    {
        QMessageBox::warning(this, "????????????", "????????????????????????");
        return;
    }

    QSqlDatabase db;
    connect_to_database(db);
    QSqlQuery query(db);

    query.exec("select cId from course where cId = '" + cId + "'");

    if(!query.next())
    {
        QMessageBox::warning(this, "????????????", "????????????????????????");
        return;
    }

    query.exec("select sid,cid,object,score,teacher from score where cid = '" + cId + "' order by sid");

    if(query.size() != 0)
    {

        while(query.next())
        {
            QString sId = query.value(0).toString();
            QString cId = query.value(1).toString();
            QString object = query.value(2).toString();
            QString score = query.value(3).toString();
            QString teacher = query.value(4).toString();

            QStringList q;
            q << sId << cId << object << score << teacher;

            int rowCount = ui->gradeTable->rowCount();
            ui->gradeTable->insertRow(rowCount);

            for(int i = 0; i<q.size(); i++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(q.at(i));
                ui->gradeTable->setItem(rowCount, i, item);
            }
        }

        int columnCount = ui->gradeTable->columnCount();
        int rowCount = ui->gradeTable->rowCount();

        for(int i = 0; i <columnCount; i++)
        {
            for(int j = 0; j < rowCount; j++)
            {
                ui->gradeTable->item(j, i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
    }
    else {
        QMessageBox::warning(this, "????????????", "??????????????????????????????");
    }
}

void gradeManage::on_addGrade_button_clicked()
{
    this->hide();
    addNewGrade *ang = new addNewGrade;
    ang->show();
}

void gradeManage::on_gradeTable_cellClicked(int row, int column)
{
    column = 0;
    ui->currentSelected_label->setVisible(true);
    ui->update_gradeButton->setDisabled(false);
    ui->delete_button->setDisabled(false);

    QString sId = ui->gradeTable->item(row, 0)->text();
    QString cId = ui->gradeTable->item(row, 1)->text();

    ui->sId_lineEdit->setText(sId);
    ui->cId_lineEdit->setText(cId);
}

void gradeManage::on_update_gradeButton_clicked()
{
    bool isOk;
    QString score = QInputDialog::getText(this, "????????????", "???????????????????????????", QLineEdit::Normal, "????????????", &isOk);

    if(isOk)
    {
        QString sId = ui->sId_lineEdit->text();
        QString cId = ui->cId_lineEdit->text();

        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        bool isUpdateSuccess = query.exec(QString("update score set score = '%0' where sid = '%1' and cid = '%2'").arg(score).arg(sId).arg(cId));

        if(isUpdateSuccess)
        {
            QMessageBox::information(this, "??????", "??????????????????");
            ui->currentSelected_label->setVisible(false);
            ui->update_gradeButton->setDisabled(true);
            ui->delete_button->setDisabled(true);
            ui->sId_lineEdit->clear();
            ui->cId_lineEdit->clear();
            updataTable();
        }
        else {
            QMessageBox::warning(this, "????????????", "????????????????????????");
            ui->currentSelected_label->setVisible(false);
            ui->update_gradeButton->setDisabled(true);
            ui->delete_button->setDisabled(true);
            ui->sId_lineEdit->clear();
            ui->cId_lineEdit->clear();
        }
    }
}

void gradeManage::on_delete_button_clicked()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "????????????", "????????????????????????????????????", QMessageBox::Yes|QMessageBox::No);

    if(btn == QMessageBox::Yes)
    {
        QString sId = ui->sId_lineEdit->text();
        QString cId = ui->cId_lineEdit->text();

        QSqlDatabase db;
        connect_to_database(db);
        QSqlQuery query(db);

        bool isDeleteSuccess = query.exec(QString("delete from score where sid = '%0' and cid = '%1'").arg(sId).arg(cId));

        if(isDeleteSuccess)
        {
            QMessageBox::information(this, "??????", "????????????");
            ui->currentSelected_label->setVisible(false);
            ui->update_gradeButton->setDisabled(true);
            ui->delete_button->setDisabled(true);
            ui->sId_lineEdit->clear();
            ui->cId_lineEdit->clear();
            updataTable();
        }
        else {
            QMessageBox::warning(this, "????????????", "????????????????????????");
            ui->currentSelected_label->setVisible(false);
            ui->update_gradeButton->setDisabled(true);
            ui->delete_button->setDisabled(true);
            ui->sId_lineEdit->clear();
            ui->cId_lineEdit->clear();
        }
    }
}

void gradeManage::on_student_statistics_clicked()
{
    gradeStaticsByStu * gsbs = new gradeStaticsByStu;
    this->hide();
    gsbs->show();
}

void gradeManage::on_course_statistics_clicked()
{
    gradeStaticsByCourse *gsbc = new gradeStaticsByCourse;
    this->hide();
    gsbc->show();
}

void gradeManage::on_export_button_clicked()
{
    Table2Excel(ui->gradeTable, "????????????");
}

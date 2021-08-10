#ifndef SELECTCOURSEMANAGE_H
#define SELECTCOURSEMANAGE_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class selectCourseManage;
}

class selectCourseManage : public QWidget
{
    Q_OBJECT

public:
    explicit selectCourseManage(QWidget *parent = nullptr);
    ~selectCourseManage();

private slots:
    void on_back_button_clicked();

    void on_searchBySNo_button_clicked();

    void on_listAll_button_clicked();

    void on_searchByCId_button_clicked();

    void on_add_button_clicked();

    //void on_tableWidget_itemClicked(QTableWidgetItem *item);

    //void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_cellClicked(int row, int column);

    //void on_updata_button_clicked();

    void on_delete_button_clicked();

    void on_export_button_clicked();

private:
    Ui::selectCourseManage *ui;
    void updateTable();
};

#endif // SELECTCOURSEMANAGE_H

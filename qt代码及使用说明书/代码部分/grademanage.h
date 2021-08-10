#ifndef GRADEMANAGE_H
#define GRADEMANAGE_H

#include <QWidget>

namespace Ui {
class gradeManage;
}

class gradeManage : public QWidget
{
    Q_OBJECT

public:
    explicit gradeManage(QWidget *parent = nullptr);
    ~gradeManage();

private slots:
    void on_back_button_clicked();

    void on_listAll_button_clicked();

    void on_searchBysNo_clicked();

    void on_searchBycId_clicked();

    void on_addGrade_button_clicked();

    void on_gradeTable_cellClicked(int row, int column);

    //void on_sId_lineEdit_textChanged(const QString &arg1);

    //void on_cId_lineEdit_textChanged(const QString &arg1);

    void on_update_gradeButton_clicked();

    void on_delete_button_clicked();

    void on_student_statistics_clicked();

    void on_course_statistics_clicked();

    void on_export_button_clicked();

private:
    Ui::gradeManage *ui;
    void updataTable();
};

#endif // GRADEMANAGE_H

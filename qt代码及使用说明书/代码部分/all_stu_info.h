#ifndef ALL_STU_INFO_H
#define ALL_STU_INFO_H

#include <QWidget>
#include "global.h"
#include "studentform.h"

namespace Ui {
class all_stu_info;
}

class all_stu_info : public QWidget
{
    Q_OBJECT

public:
    explicit all_stu_info(QWidget *parent = nullptr);
    ~all_stu_info();

private slots:
    void on_back_stuButton_clicked();

    void on_export_button_clicked();

private:
    Ui::all_stu_info *ui;
};

#endif // ALL_STU_INFO_H

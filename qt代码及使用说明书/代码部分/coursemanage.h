#ifndef COURSEMANAGE_H
#define COURSEMANAGE_H

#include <QWidget>

namespace Ui {
class courseManage;
}

class courseManage : public QWidget
{
    Q_OBJECT

public:
    explicit courseManage(QWidget *parent = nullptr);
    ~courseManage();

private slots:
    void on_bakc_button_clicked();

    void on_searchButton_clicked();

    void on_listAllCourse_button_clicked();

    void on_add_button_clicked();

    void on_update_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::courseManage *ui;
};

#endif // COURSEMANAGE_H

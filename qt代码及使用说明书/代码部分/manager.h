#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>

namespace Ui {
class manager;
}

class manager : public QWidget
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

private slots:
    void on_pushButton_9_clicked();

    void on_stu_inform_guanlipushButton_clicked();

    void on_class_managepushButton_clicked();

    void on_course_manageButton_clicked();

    void on_selectCourse_manageButton_clicked();

    void on_scoremanagepushButton_clicked();

private:
    Ui::manager *ui;
};

#endif // MANAGER_H

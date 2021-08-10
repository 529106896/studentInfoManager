#ifndef ADDNEWCOURSE_H
#define ADDNEWCOURSE_H

#include <QWidget>

namespace Ui {
class addNewCourse;
}

class addNewCourse : public QWidget
{
    Q_OBJECT

public:
    explicit addNewCourse(QWidget *parent = nullptr);
    ~addNewCourse();

private slots:
    void on_back_button_clicked();

    void on_submitButton_clicked();

private:
    Ui::addNewCourse *ui;
};

#endif // ADDNEWCOURSE_H

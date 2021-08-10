#ifndef ADDNEWGRADE_H
#define ADDNEWGRADE_H

#include <QWidget>

namespace Ui {
class addNewGrade;
}

class addNewGrade : public QWidget
{
    Q_OBJECT

public:
    explicit addNewGrade(QWidget *parent = nullptr);
    ~addNewGrade();

private slots:
    void on_back_button_clicked();

    //void on_cId_lineEdit_editingFinished();

    void on_cId_lineEdit_textChanged(const QString &arg1);

    void on_submit_button_clicked();

private:
    Ui::addNewGrade *ui;
};

#endif // ADDNEWGRADE_H

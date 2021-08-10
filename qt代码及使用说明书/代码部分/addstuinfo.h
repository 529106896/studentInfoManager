#ifndef ADDSTUINFO_H
#define ADDSTUINFO_H

#include <QWidget>

namespace Ui {
class addStuInfo;
}

class addStuInfo : public QWidget
{
    Q_OBJECT

public:
    explicit addStuInfo(QWidget *parent = nullptr);
    ~addStuInfo();

private slots:
    void on_pushButton_3_clicked();

    void on_clear_button_clicked();

    void on_submit_button_clicked();

private:
    Ui::addStuInfo *ui;
};

#endif // ADDSTUINFO_H

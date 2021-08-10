#ifndef STUINFOMANAGE_H
#define STUINFOMANAGE_H

#include <QWidget>

namespace Ui {
class stuinfomanage;
}

class stuinfomanage : public QWidget
{
    Q_OBJECT

public:
    explicit stuinfomanage(QWidget *parent = nullptr);
    ~stuinfomanage();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_update_button_clicked();

    void on_addStuInfo_button_clicked();

    void on_listAllStu_button_clicked();

    void on_delete_button_clicked();

    void on_reset_button_clicked();

private:
    Ui::stuinfomanage *ui;
};

#endif // STUINFOMANAGE_H

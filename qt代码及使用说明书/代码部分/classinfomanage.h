#ifndef CLASSINFOMANAGE_H
#define CLASSINFOMANAGE_H

#include <QWidget>

namespace Ui {
class classInfoManage;
}

class classInfoManage : public QWidget
{
    Q_OBJECT

public:
    explicit classInfoManage(QWidget *parent = nullptr);
    ~classInfoManage();

private slots:
    void on_back_button_clicked();

    void on_search_button_clicked();

    void on_listAll_button_clicked();

    void on_add_button_clicked();

    void on_update_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::classInfoManage *ui;
};

#endif // CLASSINFOMANAGE_H

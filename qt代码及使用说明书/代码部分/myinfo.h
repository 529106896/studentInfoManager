#ifndef MYINFO_H
#define MYINFO_H

#include <QWidget>

namespace Ui {
class myInfo;
}

class myInfo : public QWidget
{
    Q_OBJECT

public:
    explicit myInfo(QWidget *parent = nullptr);
    ~myInfo();

private slots:
    void on_back_button_clicked();

    void on_resetPwd_button_clicked();

private:
    Ui::myInfo *ui;
};

#endif // MYINFO_H

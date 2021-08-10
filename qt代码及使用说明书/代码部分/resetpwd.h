#ifndef RESETPWD_H
#define RESETPWD_H

#include <QWidget>

namespace Ui {
class resetPwd;
}

class resetPwd : public QWidget
{
    Q_OBJECT

public:
    explicit resetPwd(QWidget *parent = nullptr);
    ~resetPwd();

private slots:
    void on_back_button_clicked();

    void on_oldPwd_lineEdit_textChanged(const QString &arg1);

    void on_newPwd_lineEdit_textChanged(const QString &arg1);

    void on_repeatPwd_lineEdit_textChanged(const QString &arg1);

    void on_submit_button_clicked();

private:
    Ui::resetPwd *ui;
};

#endif // RESETPWD_H

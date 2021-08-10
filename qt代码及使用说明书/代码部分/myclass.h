#ifndef MYCLASS_H
#define MYCLASS_H

#include <QWidget>

namespace Ui {
class myclass;
}

class myclass : public QWidget
{
    Q_OBJECT

public:
    explicit myclass(QWidget *parent = nullptr);
    ~myclass();

private slots:
    void on_backButton_clicked();

private:
    Ui::myclass *ui;
};

#endif // MYCLASS_H

#ifndef GRADESTATICSBYSTU_H
#define GRADESTATICSBYSTU_H

#include <QWidget>

namespace Ui {
class gradeStaticsByStu;
}

class gradeStaticsByStu : public QWidget
{
    Q_OBJECT

public:
    explicit gradeStaticsByStu(QWidget *parent = nullptr);
    ~gradeStaticsByStu();

private slots:
    void on_back_button_clicked();

    void on_start_button_clicked();

private:
    Ui::gradeStaticsByStu *ui;
};

#endif // GRADESTATICSBYSTU_H

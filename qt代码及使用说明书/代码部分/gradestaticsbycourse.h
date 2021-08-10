#ifndef GRADESTATICSBYCOURSE_H
#define GRADESTATICSBYCOURSE_H

#include <QWidget>

namespace Ui {
class gradeStaticsByCourse;
}

class gradeStaticsByCourse : public QWidget
{
    Q_OBJECT

public:
    explicit gradeStaticsByCourse(QWidget *parent = nullptr);
    ~gradeStaticsByCourse();

private slots:
    void on_back_button_clicked();

    void on_search_button_clicked();

private:
    Ui::gradeStaticsByCourse *ui;
};

#endif // GRADESTATICSBYCOURSE_H

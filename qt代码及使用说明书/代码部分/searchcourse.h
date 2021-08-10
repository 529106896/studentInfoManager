#ifndef SEARCHCOURSE_H
#define SEARCHCOURSE_H

#include <QWidget>

namespace Ui {
class searchCourse;
}

class searchCourse : public QWidget
{
    Q_OBJECT

public:
    explicit searchCourse(QWidget *parent = nullptr);
    ~searchCourse();

private slots:
    void on_backButton_clicked();

    void on_clearButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::searchCourse *ui;
};

#endif // SEARCHCOURSE_H

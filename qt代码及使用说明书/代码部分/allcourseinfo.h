#ifndef ALLCOURSEINFO_H
#define ALLCOURSEINFO_H

#include <QWidget>

namespace Ui {
class allCourseInfo;
}

class allCourseInfo : public QWidget
{
    Q_OBJECT

public:
    explicit allCourseInfo(QWidget *parent = nullptr);
    ~allCourseInfo();

private slots:
    void on_back_button_clicked();

    void on_export_button_clicked();

private:
    Ui::allCourseInfo *ui;
};

#endif // ALLCOURSEINFO_H

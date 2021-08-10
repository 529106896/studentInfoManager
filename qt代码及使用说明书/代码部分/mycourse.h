#ifndef MYCOURSE_H
#define MYCOURSE_H

#include <QWidget>

namespace Ui {
class mycourse;
}

class mycourse : public QWidget
{
    Q_OBJECT

public:
    explicit mycourse(QWidget *parent = nullptr);
    ~mycourse();

private slots:
    void on_pushButton_2_clicked();

    void on_searchButton_clicked();

    void on_export_button_clicked();

private:
    Ui::mycourse *ui;
};

#endif // MYCOURSE_H

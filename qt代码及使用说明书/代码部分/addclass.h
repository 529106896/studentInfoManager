#ifndef ADDCLASS_H
#define ADDCLASS_H

#include <QWidget>

namespace Ui {
class addClass;
}

class addClass : public QWidget
{
    Q_OBJECT

public:
    explicit addClass(QWidget *parent = nullptr);
    ~addClass();

private slots:
    void on_back_button_clicked();

    void on_submit_button_clicked();

private:
    Ui::addClass *ui;
};

#endif // ADDCLASS_H

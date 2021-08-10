#ifndef ALLCLASSINFO_H
#define ALLCLASSINFO_H

#include <QWidget>

namespace Ui {
class allClassInfo;
}

class allClassInfo : public QWidget
{
    Q_OBJECT

public:
    explicit allClassInfo(QWidget *parent = nullptr);
    ~allClassInfo();

private slots:
    void on_back_button_clicked();

    void on_export_button_clicked();

private:
    Ui::allClassInfo *ui;
};

#endif // ALLCLASSINFO_H

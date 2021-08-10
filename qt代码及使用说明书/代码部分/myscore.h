#ifndef MYSCORE_H
#define MYSCORE_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class myScore;
}

class myScore : public QWidget
{
    Q_OBJECT

public:
    explicit myScore(QWidget *parent = nullptr);
    ~myScore();

private slots:
    void on_pushButton_findcore_back_clicked();

    void on_findscoreButton_clicked();

private:
    Ui::myScore *ui;
};

#endif // MYSCORE_H

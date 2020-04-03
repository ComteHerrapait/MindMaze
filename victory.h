#ifndef VICTORY_H
#define VICTORY_H

#include <QDialog>
#include <myglwidget.h>

namespace Ui {
class Victory;
}

class Victory : public QDialog
{
    Q_OBJECT

public:
    explicit Victory(int winTime, QWidget *parent = nullptr);
    ~Victory();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Victory *ui;
};

#endif // VICTORY_H

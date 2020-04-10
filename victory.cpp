#include "victory.h"
#include "ui_victory.h"

Victory::Victory(int winTime, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Victory)
{
    ui->setupUi(this);
    //écran de victoire, on affiche le temps mit pour sortir du labyrinthe
    ui->label_3->setText(QString::number(winTime));
}

Victory::~Victory()
{
    delete ui;
}

void Victory::on_buttonBox_rejected()
{
    exit(0);
}

void Victory::on_buttonBox_accepted()
{
    close();
}

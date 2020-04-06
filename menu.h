#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QIntValidator>
#include <QString>
#include <QCloseEvent>
#include <QMessageBox>
#include "myglwidget.h"
#include <iostream>

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    unsigned int width;
    unsigned int height;
    unsigned int nbSpheres;
    unsigned int winWidth;
    unsigned int winHeight;
    unsigned int FOV;
    unsigned int volume;
    bool fullscreen;
    bool freeMovement;
    bool mouse;
    bool keyboard;
    bool camera;

private slots:
    //largeur
    void on_SliderWidth_sliderMoved(int position);
    void on_TextWidth_textEdited(const QString &arg1);

    //hauteur
    void on_SliderHeight_sliderMoved(int position);
    void on_TextHeight_textEdited(const QString &arg1);

    //nombre de spheres
    void on_SlidernbSphere_sliderMoved(int position);
    void on_TextnbSphere_textEdited(const QString &arg1);

    //FOV
    void on_SliderFOV_sliderMoved(int position);
    void on_TextFOV_textEdited(const QString &arg1);

    //Volume
    void on_SliderVolume_sliderMoved(int position);
    void on_TextVolume_textEdited(const QString &arg1);

    //Bouton Jouer
    void on_pushButton_clicked();

    //Quitter
    void on_actionQuit_changed();
    void closeEvent (QCloseEvent *event);

private:
    Ui::Menu *ui;
};

#endif // MENU_H

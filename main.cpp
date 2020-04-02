#include <QApplication>
#include <ctime>
#include "myglwidget.h"
#include "menu.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Initialisation du generateur de nombres aleatoires
    srand(time(nullptr));

    // Creation de l'application QT
    QApplication app(argc, argv);
    bool playAgain = true;
    while (playAgain){
        // Menu
        Menu* menu = new Menu();
        menu->show();
        app.exec();// Execution de l'application QT

        // Jeu
        MyGLWidget glWidget(menu); //menu en argument pour récuperer les paramètres du jeu
        glWidget.show();
        app.exec();// Execution de l'application QT

        // Victoire

        exit(0);//DEBUG
    }

    return 0;
}

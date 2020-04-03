#include <QApplication>
#include <ctime>
#include "myglwidget.h"
#include "menu.h"
#include "victory.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Initialisation du generateur de nombres aleatoires
    srand(time(nullptr));

    // Creation de l'application QT
    QApplication app(argc, argv);

    Menu* menu = new Menu();
    while (true) {
        // Menu
        menu->show();
        app.exec();// Execution de l'application QT
    }

    return 0;
}

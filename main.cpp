#include <QApplication>
#include <ctime>
#include "myglwidget.h"
#include "menu.h"
#include "victory.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /* On créé une application puis on créé un menu que l'on réaffiche à chaque fois que
     * toutes les fenêtres sont fermées.
     * Le menu se charge d'ouvrir la fenêtre de jeu, qui se charge elle même d'afficher
     * l'écran de victoire. Ces deux derniers sont supprimés à chaque partie.
     * Le menu lui est conservé pour que les paramètres restent les mêmes entre chaque
     * partie.
     */

    // Creation de l'application QT
    QApplication app(argc, argv);

    //créé en dehors de la boucle, le menu n'est pas recréé à chaque partie
    Menu* menu = new Menu();

    //Boucle infinie car l'application est close() par nimporte quelle la fenêtre
    while (true)
    {
        //on affiche ou ré-affiche le menu de configuration
        menu->show();

        app.exec();// boucle d'execution attend que toutes les fenêtres se ferment
    }

    return 0;
}

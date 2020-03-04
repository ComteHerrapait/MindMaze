#define _USE_MATH_DEFINES

#include "myglwidget.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

using namespace std;

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
}


// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la matrice projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 16.0/9.0, 0.1f, 500.0f);



    // Definition de la matrice modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(player.getPos().x, player.getPos().y, player.getPos().z, //position camera
              player.getTarget().x, player.getTarget().y, player.getTarget().z,  //position cible
              0.0f, 1.0f, 0.0f); //vecteur vertical
    cout << "(" <<player.getPos().x <<", "<< player.getPos().y <<", "<< player.getPos().z << ")" << endl;
    cout << "(" <<player.getTarget().x <<", "<< player.getTarget().y <<", "<< player.getTarget().z << ")" << endl;

    // ---------Affichage du Sol-------
    glBegin(GL_QUADS);

    glColor3ub(255, 255, 255);
    glVertex3f(-5.0f, 0, -5.0f);
    glVertex3f(5.0f, 0, -5.0f);
    glVertex3f(5.0f, 0, 5.0f);
    glVertex3f(-5.0f, 0, 5.0f);

    glEnd();
    // --------------------------------

}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
   switch(event->key())
    {
        // Cas par defaut
        case Qt::Key::Key_Q://gauche
            player.move(0,-1);
            break;
        case Qt::Key::Key_D://droite
            player.move(0,1);
            break;
        case Qt::Key::Key_Z://avant
            player.move(1,0);
            break;
        case Qt::Key::Key_S://arriere
            player.move(-1,0);
            break;

        case Qt::Key::Key_Tab:
        if (Zbuf){
            Zbuf = false;
            glDisable(GL_DEPTH_TEST);
        } else {
            Zbuf = true;
            glEnable(GL_DEPTH_TEST);
        }

        break;
        case Qt::Key::Key_Escape:
            exit(0);
        break;
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

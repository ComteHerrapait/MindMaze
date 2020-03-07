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
    gluPerspective(FOV, 16.0/9.0, 0.1f, 500.0f);



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
    glColor3ub(255, 0, 255);
    glVertex3f(5.0f, 0, -5.0f);
    glColor3ub(255, 255, 0);
    glVertex3f(5.0f, 0, 5.0f);
    glColor3ub(0, 255, 255);
    glVertex3f(-5.0f, 0, 5.0f);
    glEnd();

    //      _-_HUD 2D_-_

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
        glVertex2f(100.0, 100.0);
        glVertex2f(0.0, 100.0);
    glEnd();

}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
   switch(event->key())
    {
        // Cas par defaut
        case Qt::Key::Key_Q://gauche
            player.move(0,-0.1);
            break;
        case Qt::Key::Key_D://droite
            player.move(0,0.1);
            break;
        case Qt::Key::Key_Z://avant
            player.move(0.1,0);
            break;
        case Qt::Key::Key_S://arriere
            player.move(-0.1,0);
            break;
        case Qt::Key::Key_E:
            player.look(3,0);
            break;
        case Qt::Key::Key_A:
            player.look(-3,0);
            break;
        case Qt::Key::Key_R:
            FOV +=5;
            break;
        case Qt::Key::Key_F:
            FOV -=5;
            break;
        case Qt::Key::Key_Tab:
        if (Zbuf){
            Zbuf = false;
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_TEXTURE_2D);
        } else {
            Zbuf = true;
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_2D);
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

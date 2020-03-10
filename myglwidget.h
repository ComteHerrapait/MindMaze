#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <iostream>
#include <QGLWidget>
#include <QtOpenGL>
#include <QKeyEvent>
#include "player.h"
#include <math.h>
#include "wall.h"
#include "sphere.h"
#include "surface.h"
#define PI 3.14159265

using namespace std;

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);
private :
    QTimer timer;
    float timeElapsed = 0.0f;
    Player player = Player(Point(0,1,0), Point(1,1,0));
    bool Zbuf = true;
    float FOV = 80.0f;
    std::vector<Wall *> V_walls;
    std::vector<Sphere *> V_spheres;
    std::vector<Surface *> V_surfaces;
};

#endif // MYGLWIDGET_H

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <iostream>
#include <QGLWidget>
#include <QtOpenGL>
#include <QKeyEvent>
#include "player.h"
#include <math.h>
#define PI 3.14159265

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
    Player player = Player(Point(1,1,1), Point(0,0,10));
    bool Zbuf = true;
    float FOV = 80.0f;
};

#endif // MYGLWIDGET_H

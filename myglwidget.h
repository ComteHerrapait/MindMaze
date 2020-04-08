#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <iostream>
#include <vector>
#include <QGLWidget>
#include <QtOpenGL>
#include <QKeyEvent>
#include <random>
#include "player.h"
#include <math.h>
#include "wall.h"
#include "sphere.h"
#include "surface.h"
#include "maze.h"
#include "dj.h"
#include "skybox.h"
#include "victory.h"
#include "camera.h"
#include <QMessageBox>
#include <QSettings>

#include <QtMultimedia/QMediaPlayer>
#define PI 3.14159265

using namespace std;

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    int winTime;

protected: 
    void initializeGL();// Fonction d'initialisation
    void resizeGL(int width, int height);// Fonction de redimensionnement
    void paintGL();// Fonction d'affichage
    void keyPressEvent(QKeyEvent * event);// Fonction de gestion d'interactions clavier
    void wheelEvent(QWheelEvent *event);//Fonction de gestion d'interaction molette
    void mouseMoveEvent(QMouseEvent *event);//Fonction de gestion d'interaction souris
    void resetMinimapTimer() {sinceMoveTime = time(0);}
private :
    QTimer timer;
    float animTime = 0;
    time_t startTime;
    time_t sinceMoveTime;
    QPoint lastPosMouse;

    Player player = Player(myPoint(1,1,1), myPoint(2,1,1));
    Skybox * skybox;
    vector<Wall *> V_walls;
    vector<Sphere *> V_spheres;
    vector<Surface *> V_surfaces;
    DJ dj;
    Camera webcam;

    //PARAMETRES DE JEU
    bool mouse;
    bool camera;
    bool freeMovement;
    bool keyboard;
    unsigned int WIN_WIDTH;
    unsigned int WIN_HEIGHT;
    int nbSpheres;
    bool fullScreen;
    bool Zbuf = true;
    bool victory = false;
    int LENGTH;
    int WIDTH;
    float FOV;
    int musicVolume;
};

#endif // MYGLWIDGET_H

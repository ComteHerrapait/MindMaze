#define _USE_MATH_DEFINES

#include "myglwidget.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

#define DEBUG true //flag

using namespace std;

// Declarations des constantes
const float MAX_DIMENSION     = 50.0f;

const float SKYBOX_SIZE       = 50.0f;
const bool AUTOHIDE_MAP       = true;
const float HIDE_MAP_TIME     = 3.0;

const int ANIMATION_COUNT     = 100;

// Constructeur
MyGLWidget::MyGLWidget(Menu* menu, QWidget * parent) : QGLWidget(parent)
{
    //recuperation des paramètres
    LENGTH = menu->width;
    WIDTH = menu->height;
    nbSpheres = menu->nbSpheres;
    WIN_WIDTH = menu->winWidth;
    WIN_HEIGHT = menu->winHeight;
    FOV = menu->FOV;
    musicVolume = menu->volume;
    fullScreen = menu->fullscreen;
    freeMovement = menu->freeMovement;

    //icone de l'application
    QIcon icon = QIcon(":/maze.ico");
    setWindowIcon(icon);

    //random seed
    srand(time(0));

    //antialiasing
    setFormat(QGLFormat(QGL::SampleBuffers));

    //active le suivi de la souris
    setMouseTracking(true);

    //Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    move(screenGeometry.width()/2 - WIN_WIDTH/2, screenGeometry.height()/2 - WIN_HEIGHT/2);
    if(fullScreen) showFullScreen();

    //Connexion du timer
    connect(&timer,  &QTimer::timeout, [&] {
        updateGL();
        animTime ++;
    });
    timer.setInterval(0); //tick-rate en ms
    timer.start();

    //création du joueur
    int x = 2*rand() % (LENGTH *2)+1;
    int z = 2*rand() % (WIDTH *2) +1;
    player = Player(Point(x,1,z), Point(x+1,1,z));

}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    //creation des murs
    Maze mazegen = Maze(LENGTH,WIDTH);
    mazegen.generate();
    V_walls = mazegen.get();

    //création de la skybox
    skybox = new Skybox(SKYBOX_SIZE);

    //creation des spheres
    for (int i = 0; i < nbSpheres; i++){
        Sphere * s = new Sphere(Point(2*rand() % (LENGTH*2) +1,1,2*rand() % (WIDTH*2) +1), 0.5);
        V_spheres.push_back(s);
    }

    //creation du plafond et du sol
    Surface * ceiling = new Surface(false,LENGTH,WIDTH);//plafond
    V_surfaces.push_back(ceiling);
    Surface * floor = new Surface(true,LENGTH,WIDTH);//sol
    V_surfaces.push_back(floor);

    //démarre la musique
    dj.play("BACKGROUND");
    dj.volume("BACKGROUND",musicVolume);

    //Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    //horaire de départ
    startTime = time(0);
    sinceMoveTime = time(0) - 5;
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    //Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    //Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Continue movement animation
    if (player.isMoving()) { player.continueMove(); }

    //Verification victoire
    if (player.getPos().x < 0
            || player.getPos().x > LENGTH * 2
            || player.getPos().z < 0
            || player.getPos().z > WIDTH * 2){
        victory = true;
        showNormal();
        setMouseTracking(false);
        setCursor(Qt::ArrowCursor);
    }

    //Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_LIGHTING);

    //Definition de la matrice projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (float)WIN_WIDTH/WIN_HEIGHT, 0.1f, 250.0f);

    //Definition de la matrice modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(player.getPos().x, player.getPos().y, player.getPos().z, //position camera
              player.getTarget().x, player.getTarget().y, player.getTarget().z,  //position cible
              0.0f, 1.0f, 0.0f); //vecteur vertical
    
    // ---- Affichage de la skybox ----
    skybox->draw();
    // ---- Affichage sol et plafond ----
    for(Surface * s: V_surfaces){
        s->draw();
    }

    // ---- Affichage des Murs ----
    for(Wall * w: V_walls){
        w->draw();
    }
    // ---- Affichage des Boules ----
    bool AllSpheresFound = true;
    for(Sphere * s: V_spheres){
        s->draw(animTime);
        s->detect(player); // detecte si un joueur ramasse la sphere
        AllSpheresFound = AllSpheresFound & s->isFound(); // vérifie que toutes les spheres sont trouvées
        //son
        if (!s->isFound()){
            int d = player.getPos().distanceTo(s->getPos());
            if (100 - 15*d > 10) {
                dj.volume("SPHERESOUND", 100 - 15*d);
                dj.play("SPHERESOUND");
            } else {
                dj.volume("SPHERESOUND",0);

            }
        }
    }
    if (AllSpheresFound && !player.getAchievement()){ //evite de répeter la commande si le joueur a déjà tout trouvé
        player.foundSpheres(); // indique au joueur qu'il a trouvé toutes les spheres
        dj.stop("SPHERESOUND");
        dj.play("SPHEREFOUND");
        unsigned int size = V_walls.size();
        while (size == V_walls.size()){
            vector<Wall *>::iterator  it = V_walls.begin();
            int r = rand() % size;
            if (V_walls[r]->isOnTheEdge()){
                advance(it, r);
                V_walls.erase(it);
            }
        }
    }

    // ---- HUD 2D ----
        //paramétrage
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);

    float squareSize = 75.0f; //taille du carré de couleur
    float textBackgroudSize = 250.0f; //taille du fond du texte

    if (!victory) {
        //carré
    glBegin(GL_QUADS);
        if (player.getAchievement()) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 0.0f, 0.0f);
        }

        glVertex2f(0.0, 0.0);
        glVertex2f(squareSize, 0.0);
        glVertex2f(squareSize, squareSize);
        glVertex2f(0.0, squareSize);

        glColor3f(0.7,0.7,0.7);
        glVertex2f(squareSize, 0.0);
        glVertex2f(squareSize + textBackgroudSize,0);
        glVertex2f(squareSize + textBackgroudSize, squareSize);
        glVertex2f(squareSize, squareSize);
    glEnd();

        //MINIMAP
    float scale = 10.0;
    if (time(0) - sinceMoveTime > HIDE_MAP_TIME || !AUTOHIDE_MAP)
    {
            //Mur 2D
        for(Wall * w: V_walls){
            w->draw2D(WIN_WIDTH - LENGTH * 2 * scale - 20, 20, scale);
        }
            //Position des spheres
        for(Sphere * s: V_spheres){
            s->draw2D(WIN_WIDTH - LENGTH * 2 * scale - 20 , 20, scale);
        }
            //Position du joueur
        player.draw2D(WIN_WIDTH - LENGTH * 2 * scale - 20 , 20, scale);
    }
        //texte
    qglColor(Qt::black);
    renderText(squareSize + 20 , 20, QString("Vous jouez depuis %1 secondes").arg(time(0) - startTime));
    renderText(squareSize + 20 , 35, QString("FOV : %1 deg").arg(FOV));
    if (player.getAchievement()){
        renderText(squareSize + 20 , 50, QString("Vous avez trouvé toutes les sphères,"));
        renderText(squareSize + 20 , 65, QString("trouvez la sortie !"));
    }
    if (DEBUG) renderText(squareSize + 20 , 80, QString("coord : %1 %2 %3").arg(player.getPos().x).arg(player.getPos().y).arg(player.getPos().z));

        //modes
    if (mouse)  qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , squareSize + 25, QString("(R) Mouse"));

    if (freeMovement)   qglColor(Qt::green);
    else                qglColor(Qt::red);
    renderText(5 , squareSize + 40, QString("(T) Free movement"));

    if (camera) qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , squareSize + 55, QString("(Y) Camera"));

    if (fullScreen) qglColor(Qt::green);
    else            qglColor(Qt::red);
    renderText(5 , squareSize + 70, QString("(F) Fullscreen"));

    if (Zbuf)   qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , squareSize + 85, QString("(tab) Z-Buffer"));

    } else { // ---- VICTOIRE ----
        //carré
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        float squareSize = 900.0f; //taille du carré de couleur
        glVertex2f(WIN_WIDTH/2 - squareSize, WIN_HEIGHT/2 - squareSize);
        glVertex2f(WIN_WIDTH/2 + squareSize, WIN_HEIGHT/2 - squareSize);
        glVertex2f(WIN_WIDTH/2 + squareSize, WIN_HEIGHT/2 + squareSize);
        glVertex2f(WIN_WIDTH/2 - squareSize, WIN_HEIGHT/2 + squareSize);
    glEnd();


        //texte
    qglColor(Qt::white);
    QFont font("IM Fell English", 40);
    renderText(WIN_WIDTH/2 - 260 , WIN_HEIGHT/2 - 20, QString("Vous avez gagné!"), font);
    }
    glPopMatrix();

    // ---- MUSIQUE ----
    dj.play("BACKGROUND"); // relance la musique en permanence, pour faire une boucle
}

/*
void MyGLWidget::victory(){

}
*/

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
   if (!victory) {
       switch(event->key())
        {
            case Qt::Key::Key_Q://gauche
                if (freeMovement){player.moveWithCollisions(0,-0.1,V_walls);}
                else if (! player.isMoving())
                {player.moveWithAnimations(0,-1,ANIMATION_COUNT,V_walls);}
                resetMinimapTimer();
                break;
            case Qt::Key::Key_D://droite
                if (freeMovement){player.moveWithCollisions(0,0.1,V_walls);}
                else if (! player.isMoving())
                {player.moveWithAnimations(0,1,ANIMATION_COUNT,V_walls);}
                resetMinimapTimer();
                break;
            case Qt::Key::Key_Z://avant
                //player.move(0.1,0);
                if (freeMovement) {player.moveWithCollisions(0.1,0,V_walls);}
                else if (! player.isMoving())
                {player.moveWithAnimations(1,0,ANIMATION_COUNT,V_walls);}
                resetMinimapTimer();
                break;
            case Qt::Key::Key_S://arriere
                if (freeMovement){player.moveWithCollisions(-0.1,0,V_walls);}
                else if (! player.isMoving())
                {player.moveWithAnimations(-1,0,ANIMATION_COUNT,V_walls);}
                resetMinimapTimer();
                break;
            case Qt::Key::Key_E:
                if (freeMovement){player.look(3);}
                else if (! player.isMoving())
                {player.lookWithAnimations(1,ANIMATION_COUNT);}
                break;
            case Qt::Key::Key_A:
                if (freeMovement){player.look(-3);}
                else if (! player.isMoving())
                {player.lookWithAnimations(-1,ANIMATION_COUNT);}
                break;
            case Qt::Key::Key_R:
                mouse ^= true;
                setMouseTracking(mouse);
                if (mouse) {
                    setCursor(Qt::CrossCursor);
                } else {
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case Qt::Key::Key_T:
               freeMovement ^= true;
               if (!freeMovement){
                   player.roundPosition();
               }
               break;
            case Qt::Key::Key_Y:
               camera ^= true;
               break;
            case Qt::Key::Key_F:
                if (fullScreen){
                    showNormal();
                } else {
                    showFullScreen();
                }
                fullScreen ^= true;
                break;
            case Qt::Key::Key_Tab:
                if (Zbuf){
                    glDisable(GL_DEPTH_TEST);
                    glDisable(GL_TEXTURE_2D);
                } else {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_TEXTURE_2D);
                }
                Zbuf ^= true;
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
    } else {
       switch(event->key()){
       case Qt::Key::Key_Escape:
       case Qt::Key_Space:
           close();
       break;
       default:
           event->ignore();
           return;
       }
    }
    //Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();

}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    float deg = event->angleDelta().y();

    if (deg < 0){
        FOV --;
    } else if ( deg > 0) {
        FOV ++;
    }
    event->accept();
    updateGL();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event){
    if (mouse){
        //tourne la caméra en fonction du mouvement de la souris
        float dx = event->x() - lastPosMouse.x();

        if (freeMovement) {
            player.look(dx/4.0f);
        } else if (!player.isMoving()) {
            if (dx > 20) {
                player.lookWithAnimations(1,ANIMATION_COUNT);
            }
            else if (dx < -20) {
                player.lookWithAnimations(-1,ANIMATION_COUNT);
            }
        }
        //garde la souris au centre
        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
        lastPosMouse = QPoint(width()/2,height()/2);
    }
}


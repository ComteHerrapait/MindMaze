#define _USE_MATH_DEFINES

#include "myglwidget.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

#define DEBUG true //flag
#define LOADSETTINGS QSettings settings("resources/settings.ini",QSettings::IniFormat)
using namespace std;

// Declarations des constantes
const float MAX_DIMENSION     = 50.0f;

const float SKYBOX_SIZE       = 50.0f;
const bool AUTOHIDE_MAP       = true;
const float HIDE_MAP_TIME     = 3.0;
const float CAMERA_SENSITIVITY= 30.0;
const int ANIMATION_COUNT     = 30;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent)
{
    // attribution des paramètres
    LOADSETTINGS;
    mouse = settings.value("Features/mouse").toBool();
    camera = settings.value("Features/camera").toBool();
    freeMovement = !settings.value("Features/snapping").toBool();
    keyboard = settings.value("Features/keyboard").toBool();
    WIN_WIDTH  = settings.value("Display/winWidth").toInt();
    WIN_HEIGHT = settings.value("Display/winHeight").toInt();
    nbSpheres = settings.value("Maze/nbSpheres").toInt();
    fullScreen = settings.value("Display/fullscreen").toBool();
    LENGTH = settings.value("Maze/width").toInt();
    WIDTH = settings.value("Maze/height").toInt();
    FOV = settings.value("Display/FOV").toInt();
    musicVolume = settings.value("Features/volume").toInt();

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
    if(settings.value("Display/fullscreen").toBool()) showFullScreen();

    //Connexion du timer
    connect(&timer,  &QTimer::timeout, [&] {
        updateGL();
        animTime ++;
    });
    timer.setInterval(0); //tick-rate en ms
    timer.start();

    //création du joueur
    int x = 2*rand() % (settings.value("Maze/width").toInt() *2)+1;
    int z = 2*rand() % (settings.value("Maze/height").toInt()  *2)+1;
    player = Player(myPoint(x,1,z), myPoint(x+1,1,z));

    //Initialisation Camera
    if (settings.value("Features/camera").toBool()){
        webcam.init();
    }
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    //creation des murs
        //création d'un mur de test, écrasé à la génération
    V_walls = {new Wall(myPoint(1,0,0),myPoint(1,0,1))};

    Maze mazegen = Maze(LENGTH, WIDTH);
    mazegen.generate();
    V_walls = mazegen.get();



    //création de la skybox
    skybox = new Skybox(SKYBOX_SIZE);

    //creation des spheres
    for (int i = 0; i < nbSpheres; i++){
        Sphere * s = new Sphere(myPoint(2*rand() % (LENGTH*2) +1,1,2*rand() % (WIDTH*2) +1), 0.5);
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
    if (DEBUG) cout << "fin de la génération du jeu" << endl;
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
    clock_t tStart = clock();
    vector<Point> result;
    if (camera){
        // récupère le vecteur de mouvement depuis la camera
        result = webcam.detect(true, false);
        int offX = result[0].x - result[1].x;
        int offY = result[0].y - result[1].y;

        // fait une action en fonction du resultat
        if (offY > CAMERA_SENSITIVITY){
            if (freeMovement) {player.moveWithCollisions(0.1,0,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(1,0,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
        } else if (offY < -CAMERA_SENSITIVITY) {
            if (freeMovement) {player.moveWithCollisions(-0.1,0,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(-1,0,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
        } else if (offX < -CAMERA_SENSITIVITY) {
            if (freeMovement){player.look(3);}
            else if (! player.isMoving())
            {player.lookWithAnimations(1,ANIMATION_COUNT);}
        }
        else if (offX > CAMERA_SENSITIVITY) {
            if (freeMovement){player.look(-3);}
            else if (! player.isMoving())
            {player.lookWithAnimations(-1,ANIMATION_COUNT);}
        }
    }
    // ---- CAS VICTOIRE ----
    if (victory){
        dj.stop("BACKGROUND");
        Victory* victoryWindow = new Victory(time(0) - startTime);
        webcam.~Camera();
        victoryWindow->show();
        this->close();
        return;
    }

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
    // ---- MUSIQUE ----
    dj.play("BACKGROUND"); // relance la musique en permanence, pour faire une boucle

    // ---- ECLAIRAGE ----
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat colorAmbiante_tab[] = {0.3, 0.3, 0.3, 0.0}; // Eclairage Général
    glLightfv(GL_LIGHT0, GL_AMBIENT, colorAmbiante_tab);

    GLfloat colorMatAmbiante_tab[] = {1.0, 1.0, 1.0, 0.0}; // Objets réfléchissent toute la lumière
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorMatAmbiante_tab);

    GLfloat matDiff[] = {0.0, 0.0, 0.0, 0.0}; // Permet d'éviter un problème que je ne comprends pas (Empêche la lumière de changer en fonction de l'orientation de la caméra)
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);

    glDisable(GL_LIGHTING);
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

    float cameraSize = 175.0f; //taille de la camera
    float textBackgroudSize = 250.0f; //taille du fond du texte

        //carré

    GLuint image_tex;
    if (camera) {
        //afiche la camera dans le carré
        glEnable(GL_TEXTURE_2D);
        GLuint image_tex = webcam.getTexture();
        glBindTexture(GL_TEXTURE_2D, image_tex );
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        //affiche un carré rouge ou vert suivant si on a recupéré la sphere
        glDisable(GL_TEXTURE_2D);
        if (player.getAchievement()) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
    }
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);     glVertex2f(0.0, 0.0);
        glTexCoord2i(1, 0);     glVertex2f(cameraSize, 0.0);
        glTexCoord2i(1, 1);     glVertex2f(cameraSize, cameraSize * 3/4);
        glTexCoord2i(0, 1);     glVertex2f(0.0, cameraSize * 3/4);
    glEnd();

    glDeleteTextures(1, &image_tex);
    glDisable(GL_TEXTURE_2D);

        // rectangle fond de texte
    glBegin(GL_QUADS);
        glColor3f(0.7,0.7,0.7);
        glVertex2f(cameraSize, 0.0);
        glVertex2f(cameraSize + textBackgroudSize,0);
        glVertex2f(cameraSize + textBackgroudSize, cameraSize * 3/4);
        glVertex2f(cameraSize, cameraSize * 3/4);
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
    renderText(cameraSize + 20 , 20, QString("Vous jouez depuis %1 secondes").arg(time(0) - startTime));
    renderText(cameraSize + 20 , 35, QString("FOV : %1 deg").arg(FOV));
    if (player.getAchievement()){
        qglColor(Qt::green);
        renderText(cameraSize + 20 , 50, QString("Vous avez trouvé toutes les sphères,"));
        renderText(cameraSize + 20 , 65, QString("trouvez la sortie !"));
    }
    if (DEBUG) {
        qglColor(Qt::white);
        renderText(cameraSize + 20 , 80, QString("coord : %1 %2 %3")
                          .arg(round(100 * player.getPos().x)/100)
                          .arg(round(100 * player.getPos().y)/100)
                          .arg(round(100 * player.getPos().z)/100));
        renderText(cameraSize + 20 , 95, QString("frame : %1 ms").arg((double)(clock() - tStart)/CLOCKS_PER_SEC*1000.0));
    }

        //modes
    if (mouse)  qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , cameraSize + 25, QString("(R) Mouse"));

    if (freeMovement)   qglColor(Qt::green);
    else                qglColor(Qt::red);
    renderText(5 , cameraSize + 40, QString("(T) Free movement"));

    if (camera) qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , cameraSize + 55, QString("(Y) Camera"));

    if (fullScreen) qglColor(Qt::green);
    else            qglColor(Qt::red);
    renderText(5 , cameraSize + 70, QString("(F) Fullscreen"));

    if (Zbuf)   qglColor(Qt::green);
    else        qglColor(Qt::red);
    renderText(5 , cameraSize + 85, QString("(tab) Z-Buffer"));

    if (keyboard)   qglColor(Qt::green);
    else            qglColor(Qt::red);
    renderText(5 , cameraSize + 100, QString("( ) Keyboard"));


    glPopMatrix();
}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        case Qt::Key::Key_Q://gauche
            if(!keyboard) break;
            if (freeMovement){player.moveWithCollisions(0,-0.1,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(0,-1,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
            break;
        case Qt::Key::Key_D://droite
            if(!keyboard) break;
            if (freeMovement){player.moveWithCollisions(0,0.1,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(0,1,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
            break;
        case Qt::Key::Key_Z://avant
            if(!keyboard) break;
            if (freeMovement) {player.moveWithCollisions(0.1,0,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(1,0,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
            break;
        case Qt::Key::Key_S://arriere
            if(!keyboard) break;
            if (freeMovement){player.moveWithCollisions(-0.1,0,V_walls);}
            else if (! player.isMoving())
            {player.moveWithAnimations(-1,0,ANIMATION_COUNT,V_walls);}
            resetMinimapTimer();
            break;
        case Qt::Key::Key_E:
            if(!keyboard) break;
            if (freeMovement){player.look(3);}
            else if (! player.isMoving())
            {player.lookWithAnimations(1,ANIMATION_COUNT);}
            break;
        case Qt::Key::Key_A:
            if(!keyboard) break;
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
           if (camera){
               webcam.init();
           }

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
            } else {
                glEnable(GL_DEPTH_TEST);
            }
            Zbuf ^= true;
        break;
        case Qt::Key::Key_Space:
            if (camera){
                webcam.init();
            }
        break;
        case Qt::Key::Key_Escape:
        if (QMessageBox::question( this, "Mindmaze",
                                   tr("Etes vous certain de vouloir quitter le jeu ?\n"),
                                   QMessageBox::No | QMessageBox::Yes,
                                   QMessageBox::No)
                != QMessageBox::Yes)
        {
            event->ignore();
        } else {
            event->accept();
            webcam.~Camera();
            exit(0);
        };

        break;
        default:
        {
            // Ignorer l'evenement
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


#include "wall.h"

const float PROBA_DECO = 35; //en pourcents

Wall::Wall(myPoint p1, myPoint p2, bool edge)
{
    end_1 = p1;
    end_2 = p2;
    onTheEdge =edge;

    // ---- Texture ----
    glEnable(GL_TEXTURE_2D);
    QImage texture;
    texture = QGLWidget::convertToGLFormat(QImage(QString(":/wall.jpg")));

    glGenTextures(1, &texMap);
    glBindTexture(GL_TEXTURE_2D, texMap );
    glTexImage2D( GL_TEXTURE_2D, // GL_TEXTURE_1D,GL_TEXTURE_2D,GL_TEXTURE_3D
                  0, // niveau de détail de l’image, avec 0 on a l’image de base
                  4, // nombre de composantes de couleurs par pixel (3 si RGB, 4 si RGBA, ...)
                  texture.width(),texture.height(), // largeur de la texture et hauteur de la texture
                  0, // toujours 0 d’après les spécif
                  GL_RGBA, // format de stockage (GL_RGB, GL_RGBA, ...)
                  GL_UNSIGNED_BYTE, // type dans lequel sont stockées les composantes(GL_UNSIGNED_BYTE, GL_BYTE, GL_INT, ...)
                  texture.bits() );  // adresse de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glDisable(GL_TEXTURE_2D);

    //---- Decoration ----
    float offset = width + 0.01; //legerement plus grand que l'épaisseur pour le mettre par dessus le mur
    if (p1.z == p2.z){
        if ((rand() % 100) < PROBA_DECO) V_decorators.push_back(new Decorator(myPoint(p1.x+0.5, 0.5, p1.z+offset),myPoint(p2.x-0.5, 1.5, p2.z+offset)));
        if ((rand() % 100) < PROBA_DECO) V_decorators.push_back(new Decorator(myPoint(p1.x+0.5, 0.5, p1.z-offset),myPoint(p2.x-0.5, 1.5, p2.z-offset)));
    } else if (p1.x == p2.x){
        if ((rand() % 100) < PROBA_DECO) V_decorators.push_back(new Decorator(myPoint(p1.x+offset, 0.5, p1.z+0.5),myPoint(p2.x+offset, 1.5, p2.z-0.5)));
        if ((rand() % 100) < PROBA_DECO) V_decorators.push_back(new Decorator(myPoint(p1.x-offset, 0.5, p1.z+0.5),myPoint(p2.x-offset, 1.5, p2.z-0.5)));
    }



}

vector<myPoint> Wall::createBase(myPoint p1, myPoint p2, float width){
    vector<myPoint> result;
    float wX, wZ;

    if (p1.z == p2.z){ //mur selon l'axe X
        if (p1.x > p2.x){
            wX = - width;
        } else {
            wX = + width;
        }
        wZ = width;
        result.push_back(myPoint(p2.x+wX,0,p2.z+wZ));
        result.push_back(myPoint(p1.x-wX,0,p1.z+wZ));
        result.push_back(myPoint(p1.x-wX,0,p1.z-wZ));
        result.push_back(myPoint(p2.x+wX,0,p2.z-wZ));
    } else if (p1.x == p2.x){// mur selon l'axe Z
        if (p1.z > p2.z){
            wZ = - width;
        } else {
            wZ = + width;
        }
        wX = width;
        result.push_back(myPoint(p2.x-wX,0,p2.z+wZ));
        result.push_back(myPoint(p1.x-wX,0,p1.z-wZ));
        result.push_back(myPoint(p1.x+wX,0,p1.z-wZ));
        result.push_back(myPoint(p2.x+wX,0,p2.z+wZ));
    }
    return result;
}
void Wall::draw(){ 
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    vector<myPoint> base = createBase(end_1, end_2, width);
    myPoint p1,p2,p3,p4;
    p1 = base[0];
    p2 = base[1];
    p3 = base[2];
    p4 = base[3];

    glBindTexture(GL_TEXTURE_2D,texMap);
    glPushMatrix();

    // ECLAIRAGE
    GLfloat wall[] = {0.6, 0.6, 0.6, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, wall);


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);//couleur

    /*    //Bottom
    glVertex3f(p1.x, 0, p1.z);
    glVertex3f(p2.x, 0, p2.z);
    glVertex3f(p3.x, 0, p3.z);
    glVertex3f(p4.x, 0, p4.z);
        //Top
    glVertex3f(p1.x, height, p1.z);
    glVertex3f(p2.x, height, p2.z);
    glVertex3f(p3.x, height, p3.z);
    glVertex3f(p4.x, height, p4.z);

    On ne voit pas le dessus et le dessous des murs
    */

        //Walls
    glNormal3i(int(p1.z == p2.z), 0, int(p1.x == p2.x));
    glTexCoord2f(0,0);  glVertex3f(p1.x, 0, p1.z);
    glTexCoord2f(1,0);  glVertex3f(p2.x, 0, p2.z);
    glTexCoord2f(1,1);  glVertex3f(p2.x, height, p2.z);
    glTexCoord2f(0,1);  glVertex3f(p1.x, height, p1.z);

    glNormal3i(int(p2.z == p3.z), 0, int(p2.x == p3.x));
    glTexCoord2f(0,0);  glVertex3f(p2.x, 0, p2.z);
    glTexCoord2f(1,0);  glVertex3f(p3.x, 0, p3.z);
    glTexCoord2f(1,1);  glVertex3f(p3.x, height, p3.z);
    glTexCoord2f(0,1);  glVertex3f(p2.x, height, p2.z);

    glNormal3i(int(p3.z == p4.z), 0, int(p3.x == p4.x));
    glTexCoord2f(0,0);  glVertex3f(p3.x, 0, p3.z);
    glTexCoord2f(1,0);  glVertex3f(p4.x, 0, p4.z);
    glTexCoord2f(1,1);  glVertex3f(p4.x, height, p4.z);
    glTexCoord2f(0,1);  glVertex3f(p3.x, height, p3.z);

    glNormal3i(int(p4.z == p1.z), 0, int(p4.x == p1.x));
    glTexCoord2f(0,0);  glVertex3f(p4.x, 0, p4.z);
    glTexCoord2f(1,0);  glVertex3f(p1.x, 0, p1.z);
    glTexCoord2f(1,1);  glVertex3f(p1.x, height, p1.z);
    glTexCoord2f(0,1);  glVertex3f(p4.x, height, p4.z);

    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // affichage des decorateurs
    for(Decorator * d:V_decorators){
        d->draw();
    }
}

void Wall::draw2D(float offX, float offY, float scale)
{

    float wX = 0;
    float wY = 0;
    float width2D = 3 * scale * width;

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    if (end_1.z == end_2.z){ //mur selon l'axe X
        if (end_1.x > end_2.x){
            wX = - width2D;
        } else {
            wX = + width2D;
        }
        wY = width2D;
        glVertex2f(offX + end_1.x*scale - wX , offY + end_1.z*scale - wY);
        glVertex2f(offX + end_2.x*scale + wX , offY + end_2.z*scale - wY);
        glVertex2f(offX + end_2.x*scale + wX , offY + end_2.z*scale + wY);
        glVertex2f(offX + end_1.x*scale - wX , offY + end_1.z*scale + wY);


    } else if (end_1.x == end_2.x){// mur selon l'axe Z
        if (end_1.z > end_2.z){
            wY = - width2D;
        } else {
            wY = + width2D;
        }
        wX = width2D;
        glVertex2f(offX + end_1.x*scale + wX , offY + end_1.z*scale - wY);
        glVertex2f(offX + end_2.x*scale + wX , offY + end_2.z*scale + wY);
        glVertex2f(offX + end_2.x*scale - wX , offY + end_2.z*scale + wY);
        glVertex2f(offX + end_1.x*scale - wX , offY + end_1.z*scale - wY);

    }
    glEnd();
}

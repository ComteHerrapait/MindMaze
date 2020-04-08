#include "wall.h"

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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D,texMap);

    vector<myPoint> base = createBase(end_1, end_2, width);
    myPoint p1,p2,p3,p4;
    p1 = base[0];
    p2 = base[1];
    p3 = base[2];
    p4 = base[3];

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);//couleur

        //Walls
    glNormal3i(1,0,0);
    glTexCoord2f(0,0);  glVertex3f(p1.x, 0, p1.z);
    glTexCoord2f(1,0);  glVertex3f(p2.x, 0, p2.z);
    glTexCoord2f(1,1);  glVertex3f(p2.x, height, p2.z);
    glTexCoord2f(0,1);  glVertex3f(p1.x, height, p1.z);

    glNormal3i(1,0,0);
    glTexCoord2f(0,0);  glVertex3f(p2.x, 0, p2.z);
    glTexCoord2f(1,0);  glVertex3f(p3.x, 0, p3.z);
    glTexCoord2f(1,1);  glVertex3f(p3.x, height, p3.z);
    glTexCoord2f(0,1);  glVertex3f(p2.x, height, p2.z);

    glNormal3i(0,1,0);
    glTexCoord2f(0,0);  glVertex3f(p3.x, 0, p3.z);
    glTexCoord2f(1,0);  glVertex3f(p4.x, 0, p4.z);
    glTexCoord2f(1,1);  glVertex3f(p4.x, height, p4.z);
    glTexCoord2f(0,1);  glVertex3f(p3.x, height, p3.z);

    glNormal3i(0,1,0);
    glTexCoord2f(0,0);  glVertex3f(p4.x, 0, p4.z);
    glTexCoord2f(1,0);  glVertex3f(p1.x, 0, p1.z);
    glTexCoord2f(1,1);  glVertex3f(p1.x, height, p1.z);
    glTexCoord2f(0,1);  glVertex3f(p4.x, height, p4.z);

    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
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

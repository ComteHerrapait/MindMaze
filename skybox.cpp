#include "skybox.h"

Skybox::Skybox(int distance)
{
    skyDistance = distance;
    // ---- Texture ----
    glEnable(GL_TEXTURE_2D);
    QImage texture;
    texture = QGLWidget::convertToGLFormat(QImage(QString(":/skybox.jpg")));

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

void Skybox::draw(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texMap);
    int t = skyDistance;
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    //X+
    glTexCoord2f(0.25, (float)1/3);     glVertex3f(t, -t, -t);
    glTexCoord2f(0.5 , (float)1/3);     glVertex3f(t, -t,  t);
    glTexCoord2f(0.5 , (float)2/3);     glVertex3f(t,  t,  t);
    glTexCoord2f(0.25, (float)2/3);     glVertex3f(t,  t, -t);
    //X-
    glTexCoord2f(1   , (float)1/3);     glVertex3f(-t, -t, -t);
    glTexCoord2f(0.75, (float)1/3);     glVertex3f(-t, -t,  t);
    glTexCoord2f(0.75, (float)2/3);     glVertex3f(-t,  t,  t);
    glTexCoord2f(1   , (float)2/3);     glVertex3f(-t,  t, -t);
    //Y+
    glTexCoord2f(0.75, (float)1/3);     glVertex3f(-t, -t,  t);
    glTexCoord2f(0.75, (float)2/3);     glVertex3f(-t,  t,  t);
    glTexCoord2f(0.5 , (float)2/3);     glVertex3f( t,  t,  t);
    glTexCoord2f(0.5 , (float)1/3);     glVertex3f( t, -t,  t);
    //Y-
    glTexCoord2f(0   , (float)1/3);     glVertex3f(-t, -t, -t);
    glTexCoord2f(0   , (float)2/3);     glVertex3f(-t,  t, -t);
    glTexCoord2f(0.25, (float)2/3);     glVertex3f( t,  t, -t);
    glTexCoord2f(0.25, (float)1/3);     glVertex3f( t, -t, -t);
    //TOP
    glTexCoord2f(0.25, 1);              glVertex3f(-t,  t, -t);
    glTexCoord2f(0.25, (float)2/3);     glVertex3f( t,  t, -t);
    glTexCoord2f(0.5 , (float)2/3);     glVertex3f( t,  t,  t);
    glTexCoord2f(0.5 , 1);              glVertex3f(-t,  t,  t);
    //BOTTOM
    glTexCoord2f(0.25, 0);              glVertex3f(-t, -t, -t);
    glTexCoord2f(0.25, (float)1/3);     glVertex3f( t, -t, -t);
    glTexCoord2f(0.5 , (float)1/3);     glVertex3f( t, -t,  t);
    glTexCoord2f(0.5 , 0);              glVertex3f(-t, -t,  t);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

#include "surface.h"

Surface::Surface(bool isFloor)
{
    if (isFloor){
        height = 0.0f;
    } else {
        height = 2.0f;
    }

    // ---- Texture ----
    glEnable(GL_TEXTURE_2D);
    QImage texture;
    if (height == 0){
        texture = QGLWidget::convertToGLFormat(QImage(QString(":/floor2.jpg")));
    }else {
        texture = QGLWidget::convertToGLFormat(QImage(QString(":/ceiling1.jpg")));
    }
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Répétition de la texture pour la dimension horizontale
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Répétition de la texture pour la dimension verticale
    glDisable(GL_TEXTURE_2D);
}

void Surface::draw(){
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,texMap);

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glTexCoord2f(0, 0);                 glVertex3f(0, height, 0);
    glTexCoord2f(LENGTH*2, 0);          glVertex3f(LENGTH*2, height, 0);
    glTexCoord2f(LENGTH*2, WIDTH*2);    glVertex3f(LENGTH*2, height, WIDTH*2);
    glTexCoord2f(0, 12);                glVertex3f(0, height, WIDTH*2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

#include "decorator.h"

Decorator::Decorator(myPoint corner1_, myPoint corner2_)
{
    //génère les 4 coins de la texture à partir des 2 en arguments
    p1 = corner1_;
    p3 = corner2_;
    if (corner1_.x == corner2_.x){
        norm[0] = 1;
        p2 = myPoint(corner1_.x,corner1_.y,corner2_.z);
        p4 = myPoint(corner1_.x,corner2_.y,corner1_.z);
    } else if (corner1_.y == corner2_.y){
        norm[1] = 1;
        p2 = myPoint(corner2_.x,corner1_.y,corner1_.z);
        p4 = myPoint(corner1_.x,corner1_.y,corner2_.z);
    } else if (corner1_.z == corner2_.z){
        norm[2] = 1;
        p2 = myPoint(corner2_.x,corner1_.y,corner1_.z);
        p4 = myPoint(corner1_.x,corner2_.y,corner1_.z);
    }

    //récupère une texture aléatoire dans le dossier prévu à cet effet
    glEnable(GL_TEXTURE_2D);
    QDir directory("resources/textures/decorators");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    QString selected = "resources/textures/decorators/" + images[rand() % images.size()];
    QImage texture = QGLWidget::convertToGLFormat(QImage(selected));

    //bind et règle la texture choisie
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

void Decorator::draw(){
    //affiche le decorateur, avec texture et eclairage
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D,texMap);
    GLfloat floor[] = {0.6, 0.6, 0.6, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, floor);
    glNormal3d(norm[0], norm[1], norm[2]);

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glTexCoord2f(0, 0);    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(1, 0);    glVertex3f(p2.x, p2.y, p2.z);
    glTexCoord2f(1, 1);    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(0, 1);    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);


}

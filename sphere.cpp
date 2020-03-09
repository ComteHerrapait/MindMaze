#include "sphere.h"

Sphere::Sphere(Point p, float r){
     radius = r ;
     pos = p;

     color[0] = 1.0f; //red
     color[1] = 0.1f; //blue
     color[2] = 0.1f; //green
     quadric = gluNewQuadric();
}
void Sphere::draw(){
    // paramètres d'affichages //
    GLenum drawMode = GLU_FILL; //mode de dessin des spheres
    int stacks = 25;            //nombre de stacks des spheres

    glPushMatrix();

    // éclairage matériau
    GLfloat couleur[] = {color[0], color[1], color[2], 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, couleur);


    // Couleur de l'objet
    glColor3f(color[0], color[1], color[2]);


    // Affichage de la quadrique
    glEnable(GL_LIGHTING);
    gluQuadricDrawStyle(quadric, drawMode);
    glTranslatef(pos.x, pos.y, pos.z);
    gluSphere(quadric, radius, stacks, stacks);//tracé de la sphere
    glDisable(GL_LIGHTING);

    glPopMatrix();
}

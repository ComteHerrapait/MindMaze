#include "sphere.h"

Sphere::Sphere(Point p, float r){
     radius = r ;
     pos = p;

     color[0] = 1.0f; //red
     color[1] = 1.0f; //blue
     color[2] = 1.0f; //green

     // Texture

     QImage texture = QGLWidget::convertToGLFormat(QImage(QString(":/tse3.jpg")));

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

     quadric = gluNewQuadric();
     gluQuadricTexture( quadric, GL_TRUE );//activation de la texture sur la quadrique
}
void Sphere::draw(float time_){

    cout << time_ << endl;
    if (found) return; //ne trace pas la boule si elle est trouvée

    // paramètres d'affichages //
    GLenum drawMode = GLU_FILL; //mode de dessin des spheres
    int stacks = 50;            //nombre de stacks des spheres

    glPushMatrix();

    // plaquage de textures
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texMap );

    //placement de la lampe
    GLfloat tab_sphere[] = {pos.x,pos.y,pos.z,1.0};
    //glLightfv(GL_LIGHT1,GL_POSITION, tab_sphere);

    // Couleur de l'objet
    glColor3f(color[0], color[1], color[2]);

    // Affichage de la quadrique
    gluQuadricDrawStyle(quadric, drawMode);
    glTranslatef(pos.x, pos.y + 0.2 * sin(time_/100), pos.z);
    glRotatef(270, 1.0, 0.0, 0.0); // on rend le logo visible
    glRotatef(time_/5,0.0,0.0,1.0); //on tourne avec le temps
    gluSphere(quadric, radius, stacks, stacks);//tracé de la sphere

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Sphere::detect(Player p){
    if ( found == false && pos.distanceTo(p.getPos()) < radius * 1.5 )
        found = true;

}

void Sphere::draw2D(float offX, float offY, float scale){
    if (found) return; //ne trace pas la boule si elle est trouvée

    float r = 0.6 * scale;
    float x = offX + pos.x*scale;
    float y = offY + pos.z*scale; //on prend pos.z car en 3D le y est la verticale
    glColor3f(0.0, 1.0, 0.0);
    // disque
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( x, y );
    for( float i = 0; i <= 2 * PI + 0.1; i += 0.1 )
    {
        glVertex2f( x + sin( i ) * r, y + cos( i ) * r );
    }
    glEnd();

}

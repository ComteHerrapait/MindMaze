#include "camera.h"

Camera::Camera()
{
    cap = VideoCapture(0); // open the default camera
    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        return;
    }

    if( !face_cascade.load( "./resources/haarcascade_frontalface_alt.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return;
    }
}

void Camera::init(){
    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        cap = VideoCapture(0); // open the default camera
    }

    faces = {};
    while (faces.size()==0){
        cap >> frame; //récupère une image depuis la camera

        cv::flip(frame,frame,1);// effet miroir

        cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY); //passage en niveaux de gris

        equalizeHist( frame_gray, frame_gray );//egalisation d'histogramme

        face_cascade.detectMultiScale(frame_gray, faces); //detecte les visages
    }
    // Draw green rectangle
    rectangle(frame,faces[0],Scalar(0,255,0),2);

    workingRect = faces[0];
    templateRect = Rect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);
    workingCenter = Point(workingRect.x+workingRect.width/2,workingRect.y+workingRect.height/2);

    cap >> frame1;//récupère une image depuis la camera

    cv::flip(frame1,frame1,1);// effet miroir

    cv::cvtColor(Mat(frame,workingRect),frameRect1,COLOR_BGR2GRAY);//passage en niveaux de gris

    // on créé le template recherché ensuite dans l'image
    int result_cols =  frame.cols-templateWidth  + 1;
    int result_rows = frame.rows-templateHeight + 1;
    resultImage.~Mat();
    resultImage.create( result_cols, result_rows, CV_32FC1 );
}

vector<Point> Camera::detect(bool hold, bool display)
{
    vector<Point> vecteur;


    cap >> frame2;//récupère une image depuis la camera
    cv::flip(frame2,frame2,1);// effet miroir

    //on passe en niveau de gris la partie de l'image qui nous intéresse
    cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

    // extrait le template de la frame1
    Mat templateImage(frameRect1,templateRect);
    // trouve la position du template dans l'image
    matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // créé un vecteur de déplacement
    Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

    // affiche un rectangle vert
    rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
    Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
    arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);

    vecteur.push_back(workingCenter);
    vecteur.push_back(p);

    // affiche la camera dans une fenetre si on veut
    if (display) imshow("WebCam", frame2);

    // si on le décide inverse les deux matrices pour ne capter que les mouvements au lieu des positions
    if (!hold) {
        swap(frameRect1,frameRect2);
    }
    return vecteur;
}



GLuint Camera::getTexture() {
    // génére un emplacment mémoire pour la texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Règle les paramètres d'adaptation de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //s'adapte aux formats de couleurs de l'image
    GLenum inputColourFormat = GL_BGR;
    if (frame2.channels() == 1)
    {
        inputColourFormat = GL_LUMINANCE;
    }

    //créé la texture
    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 frame2.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 frame2.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 frame2.ptr());        // The actual image data itself


    return textureID;
}

Camera::~Camera(){
    //le destructeur s'assure que toute les fenêtres sont bien refermées
    destroyWindow("WebCam");
    destroyAllWindows();
}

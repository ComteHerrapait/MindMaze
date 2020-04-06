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

    if( !face_cascade.load( "../MindMaze/resources/haarcascade_frontalface_alt.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return;
    }

    faces = {};
    while (faces.size()==0){
        cout << "tried getting face " << endl;
        // Get frame
        cap >> frame;
        // Mirror effect
        cv::flip(frame,frame,1);
        // Convert to gray
        cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
        // Equalize graylevels
        equalizeHist( frame_gray, frame_gray );
        //-- Detect faces
        face_cascade.detectMultiScale(frame_gray, faces);
    }
    // Draw green rectangle
    rectangle(frame,faces[0],Scalar(0,255,0),2);

    workingRect = faces[0];
    templateRect = Rect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);
    workingCenter = Point(workingRect.x+workingRect.width/2,workingRect.y+workingRect.height/2);

    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }


    // Get frame1
    cap >> frame1;
    // Mirror effect
    cv::flip(frame1,frame1,1);

    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame,workingRect),frameRect1,COLOR_BGR2GRAY);

    // Create the matchTemplate image result
    int result_cols =  frame.cols-templateWidth  + 1;
    int result_rows = frame.rows-templateHeight + 1;
    resultImage.~Mat();
    resultImage.create( result_cols, result_rows, CV_32FC1 );
}

vector<Point> Camera::detect(bool hold, bool display)
{
    vector<Point> vecteur;

    // Get frame2
    cap >> frame2;
    // Mirror effect
    cv::flip(frame2,frame2,1);
    // Extract working rect in frame2 and convert to gray
    cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

    // Extract template image in frame1
    Mat templateImage(frameRect1,templateRect);
    // Do the Matching between the working rect in frame2 and the templateImage in frame1
    matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // Compute the translation vector between the origin and the matching rect
    Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

    // Draw green rectangle and the translation vector
    rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
    Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
    arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);
    vecteur.push_back(workingCenter);
    vecteur.push_back(p);

    // Display frame2
    if (display) imshow("WebCam", frame2);

    // Swap matrixes
    if (!hold) {
        swap(frameRect1,frameRect2);
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return vecteur;
}

GLuint Camera::getTexture() {
    // Generate a number for our textureID's unique handle
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind to our texture handle
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set incoming texture format to:
    // GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
    // GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
    // Work out other mappings as required ( there's a list in comments in main() )
    GLenum inputColourFormat = GL_BGR;
    if (frame2.channels() == 1)
    {
        inputColourFormat = GL_LUMINANCE;
    }

    // Create the texture
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
    destroyWindow("WebCam");
    destroyAllWindows();
}

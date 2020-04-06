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

    CascadeClassifier face_cascade;
    if( !face_cascade.load( "D:/Travail/FISE2/MindMaze/resources/haarcascade_frontalface_alt.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return;
    }



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
    if (faces.size()>0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)faces.size();i++)
            rectangle(frame,faces[i],Scalar(0,255,0),2);
    }

    // Display frame
    imshow("WebCam", frame);

    workingRect = faces[0];
    //workingRect = Rect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
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
    //Mat(frame1,rect).copyTo(frameRect1);

    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame,workingRect),frameRect1,COLOR_BGR2GRAY);

    // Create the matchTemplate image result
    int result_cols =  frame.cols-templateWidth  + 1;
    int result_rows = frame.rows-templateHeight + 1;
    resultImage.create( result_cols, result_rows, CV_32FC1 );
}

vector<Point> Camera::detect(bool hold, bool display)
{
    vecteur = {};
    // Init output window
    namedWindow("WebCam",1);

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

Camera::~Camera(){
    destroyWindow("WebCam");
}

#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/video/tracking.hpp"
#include <QtOpenGL>

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

class Camera
{
public:
    Camera();
    void init();
    vector<Point> detect(bool hold, bool display);
    GLuint getTexture();
    ~Camera();
private:
    int frameWidth=512;
    int frameHeight=512;
    int templateWidth=100;
    int templateHeight=100;
    VideoCapture cap;
    Mat frame;
    Mat frame_gray;
    vector<Rect> faces;
    Rect workingRect;
    Mat frame1;
    Mat frame2;
    Mat frameRect1;
    Mat frameRect2;
    Rect templateRect;
    Mat resultImage;    // to store the matchTemplate result
    Point workingCenter;
    CascadeClassifier face_cascade;

};

#endif // CAMERA_H

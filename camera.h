#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/video/tracking.hpp"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

class Camera
{
public:
    Camera();
    vector<Point> detect(Rect workingRect, Mat frame);
};

#endif // CAMERA_H

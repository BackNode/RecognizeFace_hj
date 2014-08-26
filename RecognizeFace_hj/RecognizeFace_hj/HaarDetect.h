#ifndef HAARDETECT_H
#define HAARDETECT_H
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
using namespace std;
using namespace cv;

CvHaarClassifierCascade* Load_Haar_Cascade();

void detectFace(IplImage* frame,CvHaarClassifierCascade *faceCascade,CvRect *faceRect,int &count);

#endif
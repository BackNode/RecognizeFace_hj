#include "HaarDetect.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
CvHaarClassifierCascade* Load_Haar_Cascade()
{
	CvHaarClassifierCascade* faceCascade = NULL;
	const char *faceCascadeFilename = "cascades\\haarcascade_frontalface_alt.xml";
	faceCascade = (CvHaarClassifierCascade*)cvLoad(faceCascadeFilename,0,0,0);
	if(faceCascade==NULL)
	{
		cout<<"error in Load_Haar_Cascade:faceCascade is NULL"<<endl;
	}
	return faceCascade;
}
void detectFace(IplImage* frame,CvHaarClassifierCascade *faceCascade,CvRect *faceRect,int &count)
{
	
	const int flag = CV_HAAR_DO_CANNY_PRUNING;
	CvSeq *detectedFaces;
	CvMemStorage* storage;
	const double scale_factore = 1.1f;
	storage = cvCreateMemStorage(0);
	cvClearMemStorage(storage);
	if(faceCascade==NULL)
	{
		cout<<"error in detectFace:faceCascade is NULL!"<<endl;
		exit(1);
	}
	IplImage* grayFrame = NULL;
	grayFrame = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
	cvCvtColor(frame,grayFrame,CV_RGB2GRAY);
	detectedFaces = cvHaarDetectObjects(grayFrame,faceCascade,storage,scale_factore,3,flag,cvSize(20,20));
	count = detectedFaces->total;
	if(detectedFaces==NULL)
	{
		cout<<"error in detectFace:detectedFaces is NULL"<<endl;
	}
	for(int i=0;i<(detectedFaces->total);i++)
	{
		faceRect[i] = *(CvRect *)cvGetSeqElem(detectedFaces,i);
	}
	if(faceRect == NULL)
	{
		cout<<"error in detectFace:faceRect is NULL!"<<endl;
	}
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&grayFrame);
}
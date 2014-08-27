#include <iostream>
#include <windows.h>
//#include <conio.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\opencv.hpp>
#include "HaarDetect.h"
#include "LBPHFaceRecognizer.h"
using namespace std;
using namespace cv;

int main()
{
	CvCapture *camera;
	CvHaarClassifierCascade* faceCascade = NULL;
	CvRect faceRect[30];
	Mat faceMat[30];
	int faceCount;
	faceCascade = Load_Haar_Cascade();
	//initRecognizer(9,".\\trainingimages\\");
	if(!faceCascade)
		return 0;
	camera = cvCreateCameraCapture(0);
	if(camera==NULL)
	{
		cout<<"camera is NULL"<<endl;
		return 0;
	}
	IplImage *frame;
	Sleep(5000);    //wait for init the camera
	while(true)
	{
		faceCount = 0;
		frame = cvQueryFrame(camera);
		if(frame==NULL)
		{
			cout<<"frame is NULL"<<endl;
			break;
		}
		IplImage *grayFrame = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		cvCvtColor(frame,grayFrame,CV_RGB2GRAY);
		IplImage *resizeFace = cvCreateImage(cvSize(64,64),grayFrame->depth,grayFrame->nChannels);
		// �ӵ�ǰ֡���������������������Ͷ�Ӧ��CvRect
		detectFace(frame,faceCascade,faceRect,faceCount);

		//������⵽����������
		for(int i=0;i < faceCount;i++)
		{
			//����⵽�������洢��faceMat��
			cvSetImageROI(grayFrame,faceRect[i]);
			cvResize(grayFrame,resizeFace);
			faceMat[i] = resizeFace;
			cvResetImageROI(grayFrame);

			//���Ԥ��ƥ�������
			string outputName = predictedString(faceMat[i]);
			cout<<"Ԥ������"<<outputName<<endl;

			//��������������
			cvRectangle(frame,cvPoint(faceRect[i].x,faceRect[i].y),cvPoint(faceRect[i].x+faceRect[i].width-1,faceRect[i].y+faceRect[i].height-1), CV_RGB(0,255,0), 1, 8, 0);
		}
		cvNamedWindow("Camera",CV_WINDOW_AUTOSIZE);
		cvShowImage("Camera",frame);
		cvReleaseImage(&grayFrame);
		cvReleaseImage(&resizeFace);
		cvWaitKey(10);
	}
	destroyAllWindows();
	cvReleaseCapture(&camera);
	return 0;
}
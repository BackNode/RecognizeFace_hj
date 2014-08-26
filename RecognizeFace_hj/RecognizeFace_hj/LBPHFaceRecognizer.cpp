#include "LBPHFaceRecognizer.h"
#include <opencv2\core\core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <strstream>
using namespace std;
using namespace cv;

Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

void initRecognizer(const int num_trainingImages,const string image_Path)
{
	vector<Mat> images;
	vector<int> labels;
	for(int i=0;i < num_trainingImages;i++)
	{
		strstream ss;
		string s;
		ss << i;
		ss >> s;
		string filename;
		filename = image_Path;
		filename+= s;
		filename= filename+".jpg";
		images.push_back(imread(filename,CV_LOAD_IMAGE_GRAYSCALE));
		labels.push_back(i);
	}
	model->train(images,labels);
}
string predictedString(const Mat faceMat)
{
	string str1 = "wanghuafeng";
	string str2 = "huangjiang";
	string str3 = "women";
	int predicted = model->predict(faceMat);
	if(predicted<=3) return str1;
	else if(predicted<=6) return str2;
	else if(predicted<=8) return str3;
}
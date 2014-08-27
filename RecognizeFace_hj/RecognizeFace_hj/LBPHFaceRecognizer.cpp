#include "LBPHFaceRecognizer.h"
#include <opencv2\core\core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <strstream>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace cv;

void initRecognizer(/*const int num_trainingImages,const string image_Path*/)
{
	vector<Mat> images;
	vector<int> labels;
	string file_csv = ".\\trainingimages\\trainingImage.csv";
	read_csv(file_csv,images,labels,';');
	//for(int i=0;i < num_trainingImages;i++)
	//{
	//	strstream ss;
	//	string s;
	//	ss << i;
	//	ss >> s;
	//	string filename;
	//	filename = image_Path;
	//	filename+= s;
	//	filename= filename+".jpg";
	//	images.push_back(imread(filename,CV_LOAD_IMAGE_GRAYSCALE));
	//	labels.push_back(i);
	//}
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	model->train(images,labels);
	model->save(".\\trainingimages\\training_model.xml");
}
string predictedString(const Mat faceMat)
{
	string str1 = "wanghuafeng";
	string str2 = "huangjiang";
	string str3 = "women";
	fstream _file;
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    _file.open(".\\trainingimages\\training_model.xml",ios::in);
    if(!_file)
		{
			initRecognizer();
			model->load(".\\trainingimages\\training_model.xml");
		}
    else
      {
          model->load(".\\trainingimages\\training_model.xml");
      }
	int predicted = model->predict(faceMat);
	if(predicted<=3) return str1;
	else if(predicted<=6) return str2;
	else if(predicted<=8) return str3;
}
void read_csv(const string& csvfilename, vector<Mat>& images, vector<int>& labels, char separator) 
{
	std::ifstream file(csvfilename.c_str(), ifstream::in);//c_str()函数可用可不用，无需返回一个标准C类型的字符串
	if (!file) 
	{
		string error_message ="No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file,line))//从文本文件中读取一行字符，未指定限定符默认限定符为“/n”
	{

		stringstream liness(line);//这里采用stringstream主要作用是做字符串的分割
		getline(liness, path, separator);//读入图片文件路径以分好作为限定符
		getline(liness, classlabel);//读入图片标签，默认限定符
		if(!path.empty()&&!classlabel.empty())//如果读取成功，则将图片和对应标签压入对应容器中 
			{
				images.push_back(imread(path, 0));
				labels.push_back(atoi(classlabel.c_str()));
			}
	}
}
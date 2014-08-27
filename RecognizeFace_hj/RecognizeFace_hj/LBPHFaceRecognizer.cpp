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
	std::ifstream file(csvfilename.c_str(), ifstream::in);//c_str()�������ÿɲ��ã����践��һ����׼C���͵��ַ���
	if (!file) 
	{
		string error_message ="No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file,line))//���ı��ļ��ж�ȡһ���ַ���δָ���޶���Ĭ���޶���Ϊ��/n��
	{

		stringstream liness(line);//�������stringstream��Ҫ���������ַ����ķָ�
		getline(liness, path, separator);//����ͼƬ�ļ�·���Էֺ���Ϊ�޶���
		getline(liness, classlabel);//����ͼƬ��ǩ��Ĭ���޶���
		if(!path.empty()&&!classlabel.empty())//�����ȡ�ɹ�����ͼƬ�Ͷ�Ӧ��ǩѹ���Ӧ������ 
			{
				images.push_back(imread(path, 0));
				labels.push_back(atoi(classlabel.c_str()));
			}
	}
}
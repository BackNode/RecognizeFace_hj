#ifndef LBPH_FACE_RECOGNIZER_H
#define LBPH_FACE_RECOGNIZER_H
#include <opencv2\core\core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

void initRecognizer(/*const int num_trainingImages,const string image_Path*/);
string predictedString(const Mat faceMat);
void read_csv(const string& csvfilename, vector<Mat>& images, vector<int>& labels, char separator);
#endif
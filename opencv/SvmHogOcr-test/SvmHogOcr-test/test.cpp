#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;
int main()
{
	Mat test;
	char result[300]; //存放預測結果
	//Ptr<ml::SVM> svm = ml::SVM::create();
	//svm->Algorithm::load<ml::SVM>("HOG_SVM_DATA.xml");//加仔訓練好的數字，這裡是10K手寫數字
	Ptr<ml::SVM> svm = ml::SVM::load("HOG_SVM_DATA.xml");
		//檢測樣本
	test = imread("test.bmp", 1); //測試圖片
	if (test.empty())
	{
		cout << "not exist" << endl;
		return -1;
	}
	cout << "load image done" << endl;
	Mat trainTempImg= Mat::zeros(28, 28, CV_32F);
	
	resize(test, trainTempImg, Size(28, 28));
	HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
	vector<float>descriptors;//存放結果
	hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特徵計算
	cout << "HOG dims: " << descriptors.size() << endl;  //印出Hog特徵維數，這裡是324
	Mat SVMtrainMat(1, descriptors.size(), CV_32F);
	int n = 0;
	for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
	{
		//cvmSet(SVMtrainMat, 0, n, *iter);
		SVMtrainMat.at<float>(n) = *iter;
		n++;
	}
	//int count = svm->getVarCount();
	//cout << count << "   " << SVMtrainMat.cols << endl;
	//count = SVMtrainMat.type();
	//cout << count << endl;
	//cout << svm->getVarCount() << "   " << SVMtrainMat.cols << endl;
	
	int ret = svm->predict(SVMtrainMat);//檢測結果
	sprintf_s(result, "%d\r\n", ret);
	namedWindow("dst", 1);
	imshow("dst", test);
	cout << "result:" << result << endl;
	waitKey();

	return 0;
}

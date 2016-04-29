
#include "opencv2/opencv.hpp"
#include "windows.h"
#include "fstream"
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;
int main(int argc)
{
	//讀黨(load file)
	vector<string> img_path;//輸入文件名(path name)
	vector<int> img_catg;
	int nLine = 0;
	string buf;
	ifstream svm_data("t10knums.txt");//訓練樣本所在地(my data place)
	unsigned long n;
	int a2i;
	while (svm_data)//将训练样本文件依次读取进来 (load data)
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)//基數行圖片，偶數行標籤	(odd is picture,even is label)
			{
				a2i = atoi(buf.c_str());
				img_catg.push_back(a2i);//atoi
			}
			else
			{
				img_path.push_back(buf);//圖像路徑(picture path)
			}
		}
	}
	svm_data.close();//關閉文件(close file)

					 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					 //處理HOG特徵(get HOG)

	int nImgNum = nLine / 2;
	Mat data_mat=Mat::zeros(nImgNum, 324, CV_32FC1), res_mat=Mat::zeros(nImgNum, 1, CV_32SC1);
	Mat src, trainImg= Mat::zeros(28, 28, CV_32FC1);

	for (string::size_type i = 0; i != img_path.size(); i++)
	{
		src = imread(img_path[i].c_str(), 1);
		if (src.empty())
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}
		cout << "deal with\t" << img_path[i].c_str() << endl;
		resize(src, trainImg, cvSize(28, 28));
		HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		vector<float>descriptors;//存放结果(storge result)
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0));//HOG特徵計算(get HOG)
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			//cvmSet(data_mat, i, n, *iter);//存储HOG特征
			//data_mat.at<float>(28 * i + n) = *iter;
			data_mat.at<float>(i , n) = *iter;

			n++;
		}
		//cvmSet(res_mat, i, 0, img_catg[i]);
		//res_mat.at<float>(i) = img_catg[i];
		res_mat.row(i)= img_catg[i];
		//res_mat.at<float>(i) = i/1000;
		cout << "Done !!!: " << img_path[i].c_str() << " " << img_catg[i] << endl;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SVM

	Ptr<ml::SVM> svm = ml::SVM::create();
	// edit: the params struct got removed,
	// we use setter/getter now:
	svm->setType(ml::SVM::C_SVC);
	svm->setKernel(ml::SVM::RBF);
	svm->setGamma(0.09);

	if (svm->train(data_mat, ml::ROW_SAMPLE, res_mat)) {
		cout << "train alerady\n";
	}
	svm->save("HOG_SVM_DATA.xml");
	cout << "HOG_SVM_DATA.xml is saved !!! \n exit program" << endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//樣本測試
	Mat test;
	char result[512];
	/*
	vector<string> img_tst_path;
	ifstream img_tst("D:/SVM_TEST.txt");  //載入需要預測的圖片合集，裡面全部都放路徑，不要放標籤
	while (img_tst)
	{
		if (getline(img_tst, buf))
		{
			img_tst_path.push_back(buf);
		}
	}
	img_tst.close();
	*/
	ofstream predict_txt("SVM_PREDICT.txt");//放入預測結果
	int success = 0, fail = 0;
	for (string::size_type j = 0; j != img_path.size(); j++)//依次預測所有圖片   
	{
		test = imread(img_path[j].c_str(), 1);
		if (test.empty())
		{
			cout << " can not load the image: " << img_path[j].c_str() << endl;
			continue;
		}
		Mat trainTempImg= Mat::zeros(28, 28, 3);
		//cvZero(trainTempImg);
		resize(test, trainTempImg,Size(28,28));
		HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		vector<float>descriptors;//結果數組   
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
		//cout << "HOG dims: " << descriptors.size() << endl;
		cout << j << " pictures are done" << endl;
		Mat SVMtrainMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			//cvmSet(SVMtrainMat, 0, n, *iter);
			SVMtrainMat.col(n) = *iter;
			//SVMtrainMat.at<float>(0,n) = *iter;
			n++;
		}

		int ret = svm->predict(SVMtrainMat);//檢測結果
		if (ret == img_catg[j]) {
			success++;
		}
		else {
			++fail;
		}
		sprintf(result, "%s  %d\r\n", img_path[j].c_str(), ret);
		predict_txt << result;  //輸出檢測結果到文本 
	}
	double rate = (double)success / ((double)(success + fail));
	cout <<"the success rate is " <<rate << endl;
	predict_txt.close();
	system("pause");
	return 0;
}







/*
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;
using namespace cv;
int main()
{	vector<string>img_path;//输入文件名变量
	vector<int> img_catg;
	int nLine = 0;
	string buf;
	ifstream svm_data("t10knums.txt");//训练样本图片的路径都写在这个txt文件中，使用bat批处理文件可以得到这个txt文件
	unsigned long n;
	while (svm_data)//将训练样本文件依次读取进来
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)//注：奇数行是图片全路径，偶数行是标签
			{
				img_catg.push_back(atoi(buf.c_str()));//atoi将字符串转换成整型，标志(0,1，2，...，9)，注意这里至少要有两个类别，否则会出错
			}
			else
			{
				img_path.push_back(buf);//图像路径
			}
		}
	}
	svm_data.close();//关闭文件
	CvMat *data_mat, *res_mat;
	int nImgNum = nLine / 2; //nImgNum是样本数量，只有文本行数的一半，另一半是标签
	data_mat = cvCreateMat(nImgNum, 324, CV_32FC1);  //第二个参数，即矩阵的列是由下面的descriptors的大小决定的，可以由descriptors.size()得到，且对于不同大小的输入训练图片，这个值是不同的
	cvSetZero(data_mat);
	//类型矩阵,存储每个样本的类型标志
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);
	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(28, 28), 8, 3);//需要分析的图片，这里默认设定图片是28*28大小，所以上面定义了324，如果要更改图片大小，可以先用debug查看一下descriptors是多少，然后设定好再运行
															 //处理HOG特征
	for (string::size_type i = 0; i != img_path.size(); i++)
	{
		src = cvLoadImage(img_path[i].c_str(), 1);
		if (src == NULL)
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}
		cout << "deal with\t" << img_path[i].c_str() << endl;
		cvResize(src, trainImg);
		Mat trainImgMat;
		trainImgMat = cvarrToMat(trainImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		vector<float>descriptors;//存放结果
		hog->compute(trainImgMat, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(data_mat, i, n, *iter);//存储HOG特征
			n++;
		}
		cvmSet(res_mat, i, 0, img_catg[i]);
		cout << "Done !!!: " << img_path[i].c_str() << " " << img_catg[i] << endl;
	}
	//****************************************************************************************************************
	//SVM

	Ptr<ml::SVM> svm = ml::SVM::create();
	// edit: the params struct got removed,
	// we use setter/getter now:
	svm->setType(ml::SVM::C_SVC);
	svm->setKernel(ml::SVM::RBF);
	svm->setGamma(0.09);
	svm->train(data_mat, ml::ROW_SAMPLE, res_mat);
	svm->save("HOG_SVM_DATA.xml");
	cout << "HOG_SVM_DATA.xml is saved !!! \n exit program" << endl;
	system("pause");
	return 0;
}
*/
/*
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
using namespace cv;
using namespace cv::ml;

int main()
{
	Ptr<SVM> svm = SVM::create();
	svm->save("svm.xml");

	return 0;
}
*/
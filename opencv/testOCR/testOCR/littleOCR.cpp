/*
#include<opencv2\opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat source = imread("test.png",CV_LOAD_IMAGE_GRAYSCALE);
	Mat source_output;
	Canny(source, source_output, 50, 100);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy2;
	vector<vector<Point> > contours2;

	/// 寻找轮廓
	
	findContours(source, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	findContours(source, contours2, hierarchy2,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	double tmp=matchShapes(contours[0], contours2[0], CV_CONTOURS_MATCH_I1,0);
	cout << "tmp is " << tmp << endl;
	namedWindow("show");
	imshow("show", source_output);
	waitKey(0);
	return 0;


}
*/

/*
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/** @function main */
/*
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	src = imread("test.png", 1);

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}
*/
/** @function thresh_callback */
/*
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}

*/

//小畫家
/*
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include<opencv2\opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

IplImage * img;

void mymouse(int event, int x, int y, int flag, void* param)
{
	static int oldx, oldy, now_down = 0;
	if (event == CV_EVENT_RBUTTONDOWN) {
		cvFloodFill(img, cvPoint(x, y), cvScalar(0, 133, 133));
	}
	if (event == CV_EVENT_LBUTTONDOWN) {
		//cvCircle(img, cvPoint(x, y), 8, cvScalar(0, 0, 255));
		//cvFloodFill(img, cvPoint(x, y), cvScalar(0, 0, 255));
		oldx = x; oldy = y;
		now_down = 1;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		now_down = 0;
	}
	if (event == CV_EVENT_MOUSEMOVE && now_down == 1) {
		cvLine(img, cvPoint(x, y), cvPoint(oldx, oldy), cvScalar(255, 0, 0));
		oldx = x; oldy = y;
	}
	cvShowImage("www", img);
}

int main()
{
	img = cvCreateImage(cvSize(600, 400), 8, 3);
	cvSet(img, cvScalar(255, 255, 255));
	cvShowImage("www", img);

	cvSetMouseCallback("www", mymouse);
	waitKey(0);
	Mat mat= cvarrToMat(img);
	Mat source = imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat source_output,matoutput;
	Canny(source, source_output, 50, 100);
	Canny(mat, matoutput, 50, 100);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy2;
	vector<vector<Point> > contours2;
	

	findContours(source, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	findContours(mat, contours2, hierarchy2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	double tmp = matchShapes(contours[0], contours2[0], CV_CONTOURS_MATCH_I1,0.0);
	cout << "tmp is " << tmp << endl;
	//namedWindow("show");
	//imshow("show", contours);

	waitKey(0);
	
	
}
*/

//小畫家2.0
#define white Scalar(255,255,255)
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include<opencv2\opencv.hpp>
#include<iostream>
#include<algorithm>
using namespace cv;
using namespace std;
using namespace cv::ml;
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;

Mat  img(200,200, CV_8UC3, Scalar(255, 255, 255));
//Mat  img;
void mymouse(int event, int x, int y, int flag, void* param)
{
	static int oldx, oldy, now_down = 0;
	if (event == CV_EVENT_RBUTTONDOWN) {
		floodFill(img, Point(x, y), Scalar(255, 255, 255));
	}
	if (event == CV_EVENT_LBUTTONDOWN) {
		//cvCircle(img, cvPoint(x, y), 8, cvScalar(0, 0, 255));
		//cvFloodFill(img, cvPoint(x, y), cvScalar(0, 0, 255));
		oldx = x; oldy = y;
		now_down = 1;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		now_down = 0;
	}
	if (event == CV_EVENT_MOUSEMOVE && now_down == 1) {
		line(img, Point(x, y), Point(oldx, oldy), Scalar(0, 0, 0),3);
		oldx = x; oldy = y;
	}
	imshow("drawer", img);
}

int main()
{
	
	int min = 100, max = 120;
	//Size a(600, 400);
	//img = CreateImage(cvSize(600, 400), 8, 3);
	//cvSet(img, cvScalar(255, 255, 255));
	namedWindow("drawer");
	imshow("drawer", img);

	setMouseCallback("drawer", mymouse);
	waitKey(0);
	imwrite("test.bmp", img);
	//Mat mat = cvarrToMat(img);
	destroyAllWindows();
	/*
	//char alphabet[] = "test/A.gif";
	//Mat source = imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat source_output, matoutput;
	//Canny(source, source_output, 50, 100);
	//Canny(img, matoutput, min, max);
	//namedWindow("drawer");
	//imshow("drawer", matoutput);
	//waitKey(0);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy2;
	vector<vector<Point> > contours2;
	cvtColor(img, img, CV_BGR2GRAY);

	//findContours(source_output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	findContours(img, contours2, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	Mat result(img.size(), CV_8U, Scalar(0));
	drawContours(result, contours2, -1, Scalar(255), 3);
	namedWindow("www");
	imshow("www", result);
	waitKey(0);
	//findContours(matoutput, contours2, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	char alphabet[] = "alphabet\\test\\A.png";
	double tmp[26];
	for (int i = 0; i < 26; i++) {
		alphabet[14] = i + 'A';
		Mat source = imread(alphabet, CV_LOAD_IMAGE_GRAYSCALE);
		
		
		resize(source, source, a);
		
		if (source.empty()) {
			cout << "can't open " << alphabet << endl;
			system("pause");
			return 0;
		}
		//Canny(source, source_output, min, max);
		//imshow("drawer", source_output);
		//waitKey(0);
		findContours(source, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		//findContours(source_output, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		tmp[i] = matchShapes(contours[0], contours2[0], CV_CONTOURS_MATCH_I1, 0.0);
		cout << alphabet[14] <<" is " << tmp[i] << endl;
		//namedWindow("show");
		//imshow("show", contours);
		
	}
	double m[26];
	memcpy(m, tmp, sizeof(tmp));
	sort(m, m + 25);
	char A = 'A';
	for (int i = 0; i < 26; i++) {
		if (tmp[i] == m[0]) {
			A += i;
			cout << A <<" is matched "<< endl;
			A -= i;
		}
	}
	//namedWindow("www");
	//imshow("www", source_output);
	//waitKey(0);
	*/
	img = imread("test.bmp");
	char result[300]; //存放預測結果
	
	Ptr<ml::SVM> svm = ml::SVM::load("HOG_SVM_DATA.xml");
	Mat trainTempImg = Mat::zeros(28, 28, CV_32F);

	resize(img, trainTempImg, Size(28, 28));
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
	//namedWindow("dst", 1);
	//imshow("dst", img);
	cout << "result:" << result << endl;
	//waitKey();

	
	system("pause");
	return 0;

}
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
int main()
{
	Mat I;
	VideoCapture cap;      //capture的宣告
	cap.open(0);           //0 為預設camera

	while (cap.isOpened()) {  //確認camera能開啓
		cap >> I;

		cvtColor(I, I, CV_BGR2GRAY);
		Mat contours;
		Canny(I, contours, 125, 350);
		threshold(contours, contours, 128, 255, THRESH_BINARY);

		namedWindow("Canny");
		imshow("Canny", contours);
		waitKey(33);
		
	}
}
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
using namespace std;

int main() {
	IplImage * src = cvLoadImage("test.jpg");

	//創造和src一樣的IplImage資料結構
	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage* yuv = cvCreateImage(cvGetSize(src), 8, 3);

	//輸入圖像轉換到HSV&YUV顏色空間
	cvCvtColor(src, hsv, CV_BGR2HSV);
	cvCvtColor(src, yuv, CV_BGR2YCrCb);
	cvNamedWindow("Source-RGB", 1);
	cvShowImage("Source-RGB", src);
	cvNamedWindow("Source-HSV", 1);
	cvShowImage("Source-HSV", hsv);
	
	cvSaveImage("HSL.jpg",hsv);
	
	cvNamedWindow("Source-YUV", 1);
	cvShowImage("Source-YUV", yuv);

	cvWaitKey(0);
	return EXIT_SUCCESS;
}
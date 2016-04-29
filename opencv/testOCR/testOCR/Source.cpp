#include <iostream>
#include <string>
#include <opencv\cv.hpp>
#include <opencv\cxcore.hpp>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	string faceCascadeName = argv[1];
	// Variable declarations and initializations
	// Iterate until the user presses the Esc key
	while (true)
	{
		// Capture the current frame
		cap >> frame;
		// Resize the frame
		resize(frame, frame, Size(), scalingFactor, scalingFactor,
			INTER_AREA);
		// Convert to grayscale
		cvtColor(frame, frameGray, CV_BGR2GRAY);
		// Equalize the histogram
		equalizeHist(frameGray, frameGray);
		// Detect faces
		faceCascade.detectMultiScale(frameGray, faces, 1.1, 2,
			0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		// Draw green rectangle around the face
		for (int i = 0; i < faces.size(); i++)
		{
			Rect faceRect(faces[i].x, faces[i].y, faces[i].width,
				faces[i].height);
			// Custom parameters to make the mask fit your face. You
			may have to play around with them to make sure it works.
				int x = faces[i].x - int(0.1*faces[i].width);
			int y = faces[i].y - int(0.0*faces[i].height);
			int w = int(1.1 * faces[i].width);
			int h = int(1.3 * faces[i].height);
			// Extract region of interest (ROI) covering your face
			frameROI = frame(Rect(x, y, w, h));
			// Resize the face mask image based on the dimensions of
			the above ROI
				resize(faceMask, faceMaskSmall, Size(w, h));
			// Convert the above image to grayscale
			cvtColor(faceMaskSmall, grayMaskSmall, CV_BGR2GRAY);
			// Threshold the above image to isolate the pixels
			associated only with the face mask
				threshold(grayMaskSmall, grayMaskSmallThresh, 230, 255,
					CV_THRESH_BINARY_INV);
			// Create mask by inverting the above image (because we
			don't want the background to affect the overlay)
				bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);
			// Use bitwise "AND" operator to extract precise boundary
			of face mask
				bitwise_and(faceMaskSmall, faceMaskSmall, maskedFace,
					grayMaskSmallThresh);
			// Use bitwise "AND" operator to overlay face mask
			bitwise_and(frameROI, frameROI, maskedFrame,
				grayMaskSmallThreshInv);
			// Add the above masked images and place it in the
			original frame ROI to create the final image
				add(maskedFace, maskedFrame, frame(Rect(x, y, w, h)));
		}
		// code dealing with memory release and GUi
		return 1;
	}
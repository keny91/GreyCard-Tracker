// GreyCard-Tracker.cpp: entry point for the console application.
//

#include "stdafx.h"
//#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main()
{

	Mat frame;          //Create Matrix to store image
	VideoCapture cap;          //initialize capture
	cap.open(0);
	Mat grayscaleFrame;
	String _windowName = "OpenCV Sample";
	VideoCapture _capture;
	namedWindow(_windowName, 1);

	// Check if the default camera is opened.
	if (_capture.isOpened()) {
		cout << "No capture device set.";
		return 0;
	}

	while (1) {
		cap >> frame;          //copy webcam stream to image
		cvtColor(frame, grayscaleFrame, COLOR_BGR2GRAY);
		imshow("window", frame);          //print image to screen
		imshow(_windowName, grayscaleFrame);
		waitKey(33);          //delay 33ms
	}
	return 0;


}


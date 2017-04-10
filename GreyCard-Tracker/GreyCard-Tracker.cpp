// GreyCard-Tracker.cpp: entry point for the console application.
//

#include "stdafx.h"
#include "FunctionLib.h"

#define CAMERA_RESOLUTION_X 640
#define CAMERA_RESOLUTION_Y 480

#define FRAME_LETTERBOX_RESOLUTION_X 320
#define FRAME_LETTERBOX_RESOLUTION_Y 480


void CallBackFunc(int event, int x, int y, int flags, void* userdata);

int * state = new int();
int clickedX = 0;
int clickedY = 0;

int main()
{

	Mat frame;          //Create Matrix to store image
	VideoCapture cap;          //initialize capture
	cap.open(0);
	Mat grayscaleFrame, imgHSV;
	String _windowName = "OpenCV Sample";
	VideoCapture _capture;
	

	FunctionLib::GetRoi();

	// Check if the default camera is opened.
	if (_capture.isOpened()) {
		cout << "No capture device set." << endl << endl;
		return 0;
	}

	cout << "Select Mode:" << endl << endl;
	cout << "	1 - Color Picker Mode:" << endl;
	cout << "	2 - Default Picker Mode:" << endl<< endl;
	int mode = -1;
	string temp;
	while (mode != 1 && mode !=2) {
		cin >> temp;
		mode = stoi(temp);
		cout << mode << endl;
		if(mode != 1 && mode != 2)
			cout << "Invalid Mode input: " << mode << ", select a valid input: 1 or 2."<< endl;
	}

	switch (mode) {
	case 1:
		cout << "Selected 1." << endl;

		namedWindow(_windowName, 1);
		cap >> frame;  // Get the first image of the video

		cout << "Waiting for click input.";
		while (*state != 1) {
			namedWindow(_windowName, 1);
			imshow(_windowName, frame);          //print image to screen
			waitKey(33);          //delay 33ms
			setMouseCallback(_windowName, CallBackFunc, NULL);
		}

		cout << "" << endl;

		// Transform to the HSV Color space, where we don´t care much about the HUE value and the saturation will be minimum to be a grey. 
		// The value will be defining how dark the grey is from Black to White.
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);  
		Vec3i colorValue = FunctionLib::GetPixelInfo(imgHSV, clickedX, clickedY, true);



		while (1) {
			cap >> frame;          //copy webcam stream to image
			cvtColor(frame, grayscaleFrame, COLOR_BGR2GRAY);
			imshow("window", frame);          //print image to screen
			imshow(_windowName, grayscaleFrame);
			waitKey(33);          //delay 33ms
		}
		return 0;


		break;
	case 2:
		cout << "Selected 2." << endl;
		break;
	default:
		break;
	}




}




/// Define a click listener for the left click button. 
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		clickedX = x;
		clickedY = y;
		*state = 1;
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
}
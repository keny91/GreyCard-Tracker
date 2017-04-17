// GreyCard-Tracker.cpp: entry point for the console application.
//

#include "stdafx.h"
#include "FunctionLib.h"
#include "ColorTracking.h"

#define CAMERA_RESOLUTION_X 640
#define CAMERA_RESOLUTION_Y 480

#define FRAME_LETTERBOX_RESOLUTION_X 320
#define FRAME_LETTERBOX_RESOLUTION_Y 480


void CallBackFunc(int event, int x, int y, int flags, void* userdata);

int * state = new int();  // meant to be changed only on the asyncronous call onMouse
// Mouse click coor, could be a Vec2i
int clickedX = 0; 
int clickedY = 0;

int main()
{

	Mat frame, ColorFilteredImage;          //Create Matrix to store image
	VideoCapture cap;          //initialize capture
	cap.open("./Tracking_GreyCard.mov");
	Mat grayscaleFrame, imgHSV;
	String _windowName = "Original Frame";
	VideoCapture _capture;
	Vec3i colorValue, colorValue2;
	ColorTracking GreyFilter1, GreyFilter2;
	vector<Point> Contour;
	Scalar color(255, 50, 255);

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
		if(mode != 1 && mode != 2)
			cout << "Invalid Mode input: " << mode << ", select a valid input: 1 or 2."<< endl;
	}
	cap >> frame;  // Get the first image of the video

	switch (mode) {



	case 1:
		cout << "Selected 1." << endl;

		cout << "Waiting for click input.";
		while (*state != 1) {
			namedWindow(_windowName, 1);
			imshow(_windowName, frame);          //print image to screen
			waitKey(33);          //delay 33ms
			setMouseCallback(_windowName, CallBackFunc, NULL);
		}

		cout <<  endl;

		// Transform to the HSV Color space, where we don´t care much about the HUE value and the saturation will be minimum to be a grey. 
		// The value will be defining how dark the grey is from Black to White.
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);  
		colorValue = FunctionLib::GetPixelInfo(imgHSV, clickedX, clickedY, true);
	
		break;





	case 2:
		cout << "Selected 2." << endl;

		
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);
		colorValue = Vec3i(30,6,123);  // From Stuying Color Picker
		namedWindow(_windowName, 1);
	

		break;


	default:
		break;

	}





	GreyFilter1 = ColorTracking();
	GreyFilter1.SetColorRangeHSVGreys(colorValue, 10, 10);

	while (1) {
		//copy webcam stream to image
		if (frame.empty())
			break;
		GreyFilter1.GetColorFilteredImage(colorValue, &imgHSV);
		imshow("HSVColor Segmentation", GreyFilter1.theFilteredImage);
		ColorFilteredImage = GreyFilter1.theFilteredImage;
		FunctionLib::MorphologyOpenMat(&GreyFilter1.theFilteredImage, &ColorFilteredImage, 5);
		//FunctionLib::MorphologyCloseMat(&GreyFilter1.theFilteredImage, &ColorFilteredImage, 3);
		imshow("Closed Image", ColorFilteredImage);
		Contour = FunctionLib::FindLargestConnectedElement(ColorFilteredImage);
		
		// Draw the largest contour using previously stored index.
		//drawContours(dst, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy); 
		drawContours(frame, vector<vector<Point> >(1, Contour), -1, color, 1, 8);
		//Contour.
		Vec2i center = FunctionLib::FindCentroidOfContour(Contour);
		circle(frame, center, 3, color);

		imshow(_windowName, frame);          //print image to screen
		imshow("Error Window", ColorFilteredImage);
		waitKey(33);          //delay 33ms
		cap >> frame; // next frame
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);



	}




	return 0;


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
#include "stdafx.h"
#include "FunctionLib.h"





// Gather the vector values of the pixel. Display info if the flag indicates so.
Vec3i FunctionLib::GetPixelInfo(Mat TargetImage, int x, int y, bool displayConsoleInfo) {

	cout << "clicked on: " << x << "," << y << endl;
	cv::Vec3i pixel = TargetImage.at<cv::Vec3b>(y, x); // read pixel (x,y)
	if (displayConsoleInfo) {
		cout << "Pixel Value: " << pixel[0] << "," << pixel[1] << "," << pixel[2] << endl;
	}

	return pixel;
}



// morphological opening (removes small objects from the foreground)
void FunctionLib::MorphologyOpenMat(Mat* image, Mat *OutputImage, int maskSize) {
	erode(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	dilate(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));

}



// morphological closing (removes small holes from the foreground)
void FunctionLib::MorphologyCloseMat(Mat* image, Mat *OutputImage, int maskSize) {
	dilate(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	erode(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
}


// Do the cropping opperation.
void FunctionLib::CropImage(Mat theimage, Mat* theOutput, Rect internalFrame) {
	*theOutput = theimage(internalFrame);
}

// Given the values of the height and width of the internal frame
Rect FunctionLib::DetermineCenteredRectangle(Mat theimage, int x, int y) {

	Size s = theimage.size();
	int Yo = s.height;
	int Xo = s.width;

	int Xdist = (Xo - x) / 2;
	int Ydist = (Yo - y) / 2;
	Rect intFrame(Xdist, Ydist, x, y);
	return intFrame;

}




/// <param> HSVImage an image already converted into the HSV color space
/// </param>
/// <summary> Filter the image
/// </summary>
vector<Point> FunctionLib::FindLargestConnectedElement(Mat BinaryImage) {

	// Keep the largest object
	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	Mat dst;
	dst = BinaryImage;

	findContours(dst, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image



	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour // A contour is a one dimensional array
		if (a>largest_area) {
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour												  
		}

	}


	
	//drawContours(dst, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy); // Draw the largest contour using previously stored index.

	//rectangle(src, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);


	// Minimum size check
	/*
	vector<Point> WhitePixels;
	findNonZero(dst, WhitePixels);
	if (WhitePixels.size() < 500) {
		// None ATM
	}
	*/

	// RoundnessCheck
	/*
	
		DO SOMETHING
	
	*/


	return contours[largest_contour_index];

}



Vec2i FunctionLib::FindCentroidOfContour(vector<Point> theContour) {

	/*
	Vec2f mathCenter = Vec2f(0.f,0.f);
	
	for (int i = 0; i < theContour.size(); i++) {
		mathCenter[0] += theContour[0].x;
		mathCenter[1] += theContour[1].y;
	}

	cout << theContour.size() << endl;

	mathCenter[0] /= theContour.size();
	mathCenter[1] /= theContour.size();


	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	*/
	/// Get the moments
	vector<Moments> mu(theContour.size());
	for (int i = 0; i < theContour.size(); i++)
	{
		mu[i] = moments(theContour, false);
	}

	///  Get the mass centers:
	vector<Point2f> mc(theContour.size());
	for (int i = 0; i < theContour.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}


	return Vec2i((int)mc[0].x, (int)mc[0].y);
}




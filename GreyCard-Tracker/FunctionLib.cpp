#include "stdafx.h"
#include "FunctionLib.h"



/// <summary>  Gather the vector values of the pixel. Display info if the flag indicates so.
/// </summary>
Vec3i FunctionLib::GetPixelInfo(Mat TargetImage, int x, int y, bool displayConsoleInfo) {

	cout << "clicked on: " << x << "," << y << endl;
	cv::Vec3i pixel = TargetImage.at<cv::Vec3b>(y, x); // read pixel (x,y)
	if (displayConsoleInfo) {
		cout << "Pixel Value: " << pixel[0] << "," << pixel[1] << "," << pixel[2] << endl;
	}

	return pixel;
}



/// <summary> Morphological closing (removes small holes from the foreground)
/// </summary>
void FunctionLib::MorphologyOpenMat(Mat* image, Mat *OutputImage, int maskSize) {
	erode(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	dilate(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));

}


/// <summary> morphological opening (removes small objects from the foreground)
/// </summary>
void FunctionLib::MorphologyCloseMat(Mat* image, Mat *OutputImage, int maskSize) {
	dilate(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	erode(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
}



/// <summary> Do the cropping opperation given a rectangle.
/// </summary>
void FunctionLib::CropImage(Mat theimage, Mat* theOutput, Rect internalFrame) {
	*theOutput = theimage(internalFrame);
}


/// <summary> Given the values of the height and width of the internal frame  find the inner rectangle
/// </summary>
Rect FunctionLib::DetermineCenteredRectangle(Mat theimage, int x, int y) {

	Size s = theimage.size();
	int Yo = s.height;
	int Xo = s.width;

	int Xdist = (Xo - x) / 2;
	int Ydist = (Yo - y) / 2;
	Rect intFrame(Xdist, Ydist, x, y);
	return intFrame;

}




/// <param> Binary image from the segmentation
/// </param>
/// <summary> Get the contour with the largest amount of connected pixels.
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


	return contours[largest_contour_index];

}




/// <param> the Contour to find its center
/// </param>
/// <summary> Determine the center of the contour given the contours´s moments
/// </summary>
Vec2i FunctionLib::FindCentroidOfContour(vector<Point> theContour) {

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




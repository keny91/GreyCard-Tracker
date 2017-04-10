#include "stdafx.h"
#include "FunctionLib.h"


FunctionLib::FunctionLib()
{
}


FunctionLib::~FunctionLib()
{
}


void FunctionLib::GetRoi() {
	
}



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









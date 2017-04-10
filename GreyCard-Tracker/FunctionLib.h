#pragma once

//#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;





static class FunctionLib
{
public:
	FunctionLib();
	~FunctionLib();
	static Vec3i GetPixelInfo(Mat TargetImage, int x, int y, bool displayConsoleInfo = false);
	static void MorphologyOpenMat(Mat* image, Mat *OutputImage, int maskSize = 5);
	static void MorphologyCloseMat(Mat* image, Mat *OutputImage, int maskSize = 5);
	static void CropImage(Mat image, Mat* Outputimage, Rect internalFrame);
	static Rect DetermineCenteredRectangle(Mat theimage, int x, int y);
	static Rect CreateStandardCenteredSquare(Mat theimage, float VerticalScreenPercent);
	static void GetRoi();
};


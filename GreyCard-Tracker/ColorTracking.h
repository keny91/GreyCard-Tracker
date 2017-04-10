#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FunctionLib.h"


class ColorTracking
{

private:
	//Area Size;
	int iLowArea;
	int iHighArea;
	//Hue;
	int iLowH;
	int iHighH;
	//Saturation
	int iLowS;
	int iHighS;
	//Value
	int iLowV;
	int iHighV;
	//type of joint
	int type;

public:
	double aArea;
	ColorTracking();
	ColorTracking(Vec3i HSVcolor);
	~ColorTracking();
	int posX, posY;
	int prevPosX, prevPosY;


	Mat theFilteredImage;

	// Sets
	void SetPixelArea(int minS, int maxS);
	void SetHue(int minH, int maxH);
	void SetValue(int minv, int maxv);
	void SetSaturation(int minH, int maxH);

	bool Detected;
	static void SetColorRangeHSV(Vec3i pixel, Vec3i*MaxValue, Vec3i* MinValue);
	//static void CreateFilteredImage(Mat *Image, Mat* OutputImage, Vec3i color);
	static void GetColorFilteredImage(Vec3i HSVcolor, Mat * output, Mat * inputHSV);
	static void FilterBWbyThreshold(Mat* InputImage, Mat* OutputBW, int TH = 150);
};

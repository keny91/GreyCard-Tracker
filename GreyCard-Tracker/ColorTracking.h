#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FunctionLib.h"


/*
   Description:

   by entering a HSV color, a segmentated version of the 
   image based in a low saturated, any HUE and the variable 
   range of the parameter Value (which indicates the light/dark)

*/


// Pre-set variables grey segmentation values
#define MAX_GREY_HUE 179
#define MIN_GREY_HUE 0
#define MAX_GREY_SAT 40
#define MIN_GREY_SAT 0
#define MAX_GREY_VAL 255 // white
#define MIN_GREY_VAL 0 // black


class ColorTracking
{

private:
	// NOTE: All this values should be parsed in to 

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
	ColorTracking(Vec3i HSVcolor, Mat * inputHSV);
	~ColorTracking();
	int posX, posY;
	int prevPosX, prevPosY;


	Mat theFilteredImage;

	// Sets
	void SetPixelArea(int minS, int maxS);
	void SetHue(int minH, int maxH);
	void SetValue(int minv, int maxv);
	void SetSaturation(int minH, int maxH);
	void SetColorRangeHSVGreys(Vec3i value, int Srange = 5 , int Vrange = 10);

	bool Detected;
	static void SetColorRangeHSV(Vec3i pixel, Vec3i*MaxValue, Vec3i* MinValue);
	//static void CreateFilteredImage(Mat *Image, Mat* OutputImage, Vec3i color);
	void GetColorFilteredImage(Vec3i HSVcolor, Mat *inputImage);
};

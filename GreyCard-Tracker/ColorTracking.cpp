#include "stdafx.h"
#include "ColorTracking.h"



ColorTracking::ColorTracking()
{
}


ColorTracking::ColorTracking(Vec3i HSVcolor)
{
}



ColorTracking::~ColorTracking()
{
}


// "Sets"  Implementation


void ColorTracking::SetHue(int minH, int maxH) {
	iLowH = minH;
	iHighH = maxH;
}

void ColorTracking::SetValue(int minV, int maxV) {
	iLowV = minV;
	iHighV = maxV;
}

void ColorTracking::SetSaturation(int minS, int maxS) {
	iLowS = minS;
	iHighS = maxS;
}

void ColorTracking::SetPixelArea(int minS, int maxS) {
	iLowArea = minS;
	iHighArea = maxS;
}


void ColorTracking::SetColorRangeHSV(Vec3i value, Vec3i* MaxValue, Vec3i* MinValue) {
	// Pre-set variables
	int MaxHuelimit = 179; // Limit for openCV
	int upperSat = 255;
	int lowerSat = 150;
	int upperValue = 255;
	int lowerValue = 100;
	int range = 5;


	int Hue = value[0];
	int UpperHue = Hue + range;
	int LowerHue = Hue - range;
	if (UpperHue > MaxHuelimit)
		UpperHue = MaxHuelimit;

	if (LowerHue < 0)
		LowerHue = 0;

	// Don´t use pointers anymore
	MaxValue[0][0] = UpperHue;
	MaxValue[0][1] = upperSat;
	MaxValue[0][2] = upperValue;

	MinValue[0][0] = LowerHue;
	MinValue[0][1] = lowerSat;
	MinValue[0][2] = lowerValue;


	// case that is from  177 to 10 -> 177,178,179,0,1,2,...,10?

}



/* Get the color filtered image by getting the similar color tones. An create a segmentation using those reference tones. */
void ColorTracking::GetColorFilteredImage(Vec3i color, Mat * inputHSV, Mat *  output) {

	Vec3i MaxA = Vec3i();
	Vec3i MinA = Vec3i();
	ColorTracking::SetColorRangeHSV(color, &MaxA, &MinA);

	// Debugging info.
	//cout << "MAX:  " << MaxA[0] << MaxA[1] << MaxA[2] << endl;
	//cout << "MIN:  " << MinA[0] << MinA[1] << MinA[2] << endl;

	inRange(*inputHSV, MinA, MaxA, *output);

}
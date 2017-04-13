#include "stdafx.h"
#include "ColorTracking.h"


/// <summary> Default Constructor.
/// </summary>
ColorTracking::ColorTracking()
{
}

/// <summary> Constructor that inmediatelly proceeds to segmentation.
/// </summary>
ColorTracking::ColorTracking(Vec3i HSVcolor, Mat * inputHSV)
{

	GetColorFilteredImage(HSVcolor, inputHSV);
}


/// <summary> Default Destructor.
/// </summary>
ColorTracking::~ColorTracking()
{
}


// "Sets"  Implementation given that we are working with private values.


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

// OLD.  Used to segmentate high 
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

	// Don´t use pointers anymore -> CHANGE IT!
	MaxValue[0][0] = UpperHue;
	MaxValue[0][1] = upperSat;
	MaxValue[0][2] = upperValue;

	MinValue[0][0] = LowerHue;
	MinValue[0][1] = lowerSat;
	MinValue[0][2] = lowerValue;


	// case that is from  177 to 10 -> 177,178,179,0,1,2,...,10?

}



void ColorTracking::SetColorRangeHSVGreys(Vec3i value, int Srange, int Vrange) {
	
	int MaxHuelimit = MAX_GREY_HUE; // Limit for openCV
	int MinHuelimit = MIN_GREY_HUE;
	int MaxSatlimit = MAX_GREY_SAT;
	int MinSatlimit = MIN_GREY_SAT;
	int MaxVallimit = MAX_GREY_VAL; // white
	int MinVallimit = MIN_GREY_VAL;


	// 0 - HUE; 1 - Saturation; 2 - Value

	// Hue -> we don´t care much since we are working with low saturation colors.

	// Saturation -> Only looking for a low range =~ [0,40]?
	int Sat = value[1];  
	int UpperSat = Sat + Srange;
	int LowerSat = Sat - Srange;
	if (UpperSat > MaxSatlimit)
		UpperSat = MaxSatlimit;

	if (LowerSat < MinSatlimit)
		LowerSat = MinSatlimit;

	// Value -> Main parameter that limits the grey color search
	int Val = value[2];
	int UpperVal = Val + Vrange;
	int LowerVal = Val - Vrange;
	if (UpperVal > MaxVallimit)
		UpperVal = MaxVallimit;

	if (LowerVal < MinVallimit)
		LowerVal = MinVallimit;


	// Don´t use pointers anymore
	iLowH = MinHuelimit;
	iHighH = MaxHuelimit;

	iLowS = LowerSat;
	iHighS = UpperSat;

	iLowV = LowerVal;
	iHighV = UpperVal;

	// Debugging info.
	cout << "MAX:  " << iLowH << " ," <<iLowS << " ," << iLowV << endl;
	cout << "MIN:  " << iHighH << " ," << iHighS << " ,"  << iHighV << endl;

	// case that is from  177 to 10 -> 177,178,179,0,1,2,...,10?

}



/* Get the color filtered image by getting the similar color tones. An create a segmentation using those reference tones. */
void ColorTracking::GetColorFilteredImage(Vec3i color, Mat * inputHSV) {


	//SetColorRangeHSVGreys(color);
	// NOTE -> Make this vectors as the class baseline, instead of the "HIGH" and "LOW"
	Vec3i MinA = Vec3i(iLowH, iLowS, iLowV);
	Vec3i MaxA = Vec3i(iHighH, iHighS, iHighV);



	inRange(*inputHSV, MinA, MaxA, theFilteredImage);
}
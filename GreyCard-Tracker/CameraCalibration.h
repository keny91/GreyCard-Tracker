#pragma once
#include "FunctionLib.h"



/// <summary> Given the image,the known distance to an object, and the
/// dimensions of an object; we will calculate the focal lenght of the given camera.
///  <para>This will allow us to estimate the distance to the object in the 
/// following interactions. 
/// </para>
///  <para>To really calibrate we will require to determine 
/// </para>
/// </summary>
class CameraCalibration
{
private:
	Vec2f FocalDistance;
	Vec2f ObjectDimension;
	



public:
	CameraCalibration();
	CameraCalibration(Mat SampleImage, float Dist, float ObjDim);
	~CameraCalibration();

	int pixelsDetectedHorizontally;
	int pixelsDetectedVertially;
	Vec2f ReferencePoint; // We will be operating with the centroid.

	void SetFocalDistance(float F);
	void SetObjectDimension(float W);

	void DetermineFocalDistance(float dist, float perWidth);
	float DetermineObjectDistance(float perWidth);


};


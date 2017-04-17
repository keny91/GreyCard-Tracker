#include "stdafx.h"
#include "CameraCalibration.h"


CameraCalibration::CameraCalibration()
{
}

CameraCalibration::CameraCalibration(Mat SampleImage, float Dist, float ObjDim)
{

}


CameraCalibration::~CameraCalibration()
{
}





void CameraCalibration::SetFocalDistance(float F) {
	FocalDistance = F;
}


void CameraCalibration::SetObjectDimension(float W){
	ObjectDimension = W;
}


void CameraCalibration::DetermineFocalDistance(float dist, float perWidth) {
	FocalDistance[0] = (dist*perWidth) / ObjectDimension[0];
	FocalDistance[1] = (dist*perWidth) / ObjectDimension[1];
}


float CameraCalibration::DetermineObjectDistance(float perWidth) {
	return (ObjectDimension[0] * FocalDistance[0]) / perWidth;
}


	
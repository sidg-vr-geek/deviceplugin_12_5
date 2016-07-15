// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DevicePluginPrivatePCH.h"

#define NUM_SENSORS						4

CLSDRVIFACE *pDrvIface = NULL;
FQuat   recalibQuat[NUM_SENSORS];
FQuat	ueCalibQuat[NUM_SENSORS];

class FDevicePlugin : public IDevicePlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void GetCurrentRotation(FQuat *upperArmL, FQuat *lowerArmL, FQuat *upperArmR, FQuat *lowerArmR) override;
	virtual void RecalibrateDevice() override;
	virtual void UECalib(int index)	override;
};

IMPLEMENT_MODULE(FDevicePlugin, MDevicePlugin)



void FDevicePlugin::StartupModule()
{
	pDrvIface = new CLSDRVIFACE();

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		recalibQuat[i].W = 1.0;
		recalibQuat[i].X = 0.0;
		recalibQuat[i].Y = 0.0;
		recalibQuat[i].Z = 0.0;

		ueCalibQuat[i].W = 1.0;
		ueCalibQuat[i].X = 0.0;
		ueCalibQuat[i].Y = 0.0;
		ueCalibQuat[i].Z = 0.0;
	}

	FRotator tempRot;

	tempRot.Yaw = 0.0;
	tempRot.Pitch = -80.0;
	tempRot.Roll = 0.0;
	ueCalibQuat[0] = tempRot.Quaternion();
	ueCalibQuat[0].X *= -1.0;
	ueCalibQuat[0].Z *= -1.0;

	tempRot.Yaw = -90.0;
	tempRot.Pitch = 0.0;
	tempRot.Roll = 180.0;
	ueCalibQuat[1] = tempRot.Quaternion();
	ueCalibQuat[1].X *= -1.0;
	ueCalibQuat[1].Z *= -1.0;

	tempRot.Yaw = 0.0;
	tempRot.Pitch = 80.0;
	tempRot.Roll = 180.0;
	ueCalibQuat[2] = tempRot.Quaternion();
	//ueCalibQuat[2].X *= -1;

	tempRot.Yaw = -90.0;
	tempRot.Pitch = 0.0;
	tempRot.Roll = 0.0;
	ueCalibQuat[3] = tempRot.Quaternion();
	/*float temp = ueCalibQuat[3].Y;
	ueCalibQuat[3].Y = ueCalibQuat[3].Z;
	ueCalibQuat[3].Z = temp;*/
	//ueCalibQuat[2].X *= -1;
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FDevicePlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FDevicePlugin::UECalib(int index)
{
	// Quats to get information from driver
	FQuat armQuat;

	int calibIterations = 100;
	int calibDelayMs = 50;

	if (!pDrvIface->IsInit())
	{
		return;
	}

	armQuat.W = 0.0;
	armQuat.X = 0.0;
	armQuat.Y = 0.0;
	armQuat.Z = 0.0;

	// Collect samples
	for (int i = 0; i < calibIterations; i++)
	{
		FQuat tempQuat[NUM_SENSORS];

		// Get Calibrated Quaternion
		GetCurrentRotation(&tempQuat[0], &tempQuat[1], &tempQuat[2], &tempQuat[3]);
		armQuat += tempQuat[index];
		Sleep(50);
	}

	// Average Out
	armQuat /= calibIterations;

	// Normalize Quaternion
	armQuat = armQuat.GetNormalized();

	UE_LOG(LogTemp, Warning, TEXT("UE Calibration for Index %d : W = %f, X = %f, Y = %f, Z = %f"),
		index,
		armQuat.W,
		armQuat.X,
		armQuat.Y,
		armQuat.Z);
}

void FDevicePlugin::GetCurrentRotation(FQuat *upperArmL, FQuat *lowerArmL, FQuat *upperArmR, FQuat *lowerArmR)
{
	FQuat upperL, lowerL, upperR, lowerR;

	pDrvIface->GetCurrentRotation(&upperL, &lowerL, &upperR, &lowerR);

	UE_LOG(LogTemp, Warning, TEXT("UpperArmL From Driver. W = %f, X = %f, Y = %f, Z = %f"),
		lowerL.W,
		lowerL.X,
		lowerL.Y,
		lowerL.Z);
	UE_LOG(LogTemp, Warning, TEXT("UpperArmR From Driver. W = %f, X = %f, Y = %f, Z = %f\n"),
		lowerR.W,
		lowerR.X,
		lowerR.Y,
		lowerR.Z);

	upperL = (ueCalibQuat[0] * (recalibQuat[0] * upperL));
	lowerL = (ueCalibQuat[1] * (recalibQuat[1] * lowerL));
	upperR = (ueCalibQuat[2] * (recalibQuat[2] * upperR));
	lowerR = (ueCalibQuat[3] * (recalibQuat[3] * lowerR));

	UE_LOG(LogTemp, Warning, TEXT("UpperArmL after calibration. W = %f, X = %f, Y = %f, Z = %f"),
		lowerL.W,
		lowerL.X,
		lowerL.Y,
		lowerL.Z);
	UE_LOG(LogTemp, Warning, TEXT("UpperArmR after calibration. W = %f, X = %f, Y = %f, Z = %f\n"),
		lowerR.W,
		lowerR.X,
		lowerR.Y,
		lowerR.Z);

	upperArmL->W = upperL.W;
	upperArmL->X = upperL.X;
	upperArmL->Y = upperL.Y;
	upperArmL->Z = upperL.Z;

	lowerArmL->W = lowerL.W;
	lowerArmL->X = lowerL.X;
	lowerArmL->Y = lowerL.Y;
	lowerArmL->Z = lowerL.Z;

	upperArmR->W = upperR.W;
	upperArmR->X = upperR.X;
	upperArmR->Y = upperR.Y;
	upperArmR->Z = upperR.Z;

	lowerArmR->W = lowerR.W;
	lowerArmR->X = lowerR.X;
	lowerArmR->Y = lowerR.Y;
	lowerArmR->Z = lowerR.Z;
}

void FDevicePlugin::RecalibrateDevice()
{
	// Array to store all avarages
	FQuat avQuatArr[NUM_SENSORS];

	// Quats to get information from driver
	FQuat upperArmL, upperArmR, lowerArmL, lowerArmR;

	int calibIterations = 100;
	int calibDelayMs = 50;

	if (!pDrvIface->IsInit())
	{
		return;
	}

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		avQuatArr[i].W = 0.0;
		avQuatArr[i].X = 0.0;
		avQuatArr[i].Y = 0.0;
		avQuatArr[i].Z = 0.0;
	}

	// Collect samples
	for (int i = 0; i < calibIterations; i++)
	{
		pDrvIface->GetCurrentRotation(&upperArmL, &lowerArmL, &upperArmR, &lowerArmR);
		avQuatArr[0] += upperArmL;
		avQuatArr[1] += lowerArmL;
		avQuatArr[2] += upperArmR;
		avQuatArr[3] += lowerArmR;
		Sleep(50);
	}

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		// Average Out
		avQuatArr[i] /= calibIterations;

		// Normalize Quaternion
		avQuatArr[i] = avQuatArr[i].GetNormalized();

		// Save the inverse of this quat
		recalibQuat[i] = avQuatArr[i].Inverse();
	}
}
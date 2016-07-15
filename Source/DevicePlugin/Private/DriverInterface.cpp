#include "DevicePluginPrivatePCH.h"

#define				_CNAME "DRVIFACE"

CLSDRVIFACE::CLSDRVIFACE()
{
	bInit = false;

	InitDriver();
}

void CLSDRVIFACE::InitDriver()
{
	NmspDevDrv::CLSDEVDRV::DrvInit();
	bInit = true;
}

bool CLSDRVIFACE::IsInit()
{
	return bInit;
}

void CLSDRVIFACE::GetCurrentRotation(FQuat *upperArmL, FQuat *lowerArmL, FQuat *upperArmR, FQuat *lowerArmR)
{
	STQUAT  inRotUpperL = { 0.0 };
	STQUAT  inRotLowerL = { 0.0 };
	STQUAT  inRotUpperR = { 0.0 };
	STQUAT  inRotLowerR = { 0.0 };

	if (bInit)
	{
		NmspDevDrv::CLSDEVDRV::DrvGetRawQuat(&inRotUpperL, &inRotLowerL, &inRotUpperR, &inRotLowerR);

		/*UE_LOG(LogTemp, Warning, TEXT("2 Rotation Data Received. Pitch : UpperL = %f, LowerL = %f, UpperR = %f, LowerR = %f"),
		inRotUpperL.w,
		inRotLowerL.w,
		inRotUpperR.w,
		inRotLowerR.w);*/

		inRotLowerL.z *= -1.0;
		inRotLowerL.x *= -1.0;

		inRotUpperL.z *= -1.0;
		inRotUpperL.x *= -1.0;
	}

	upperArmL->W = inRotUpperL.w;
	upperArmL->X = inRotUpperL.x;
	upperArmL->Y = inRotUpperL.y;
	upperArmL->Z = inRotUpperL.z;

	lowerArmL->W = inRotLowerL.w;
	lowerArmL->X = inRotLowerL.x;
	lowerArmL->Y = inRotLowerL.y;
	lowerArmL->Z = inRotLowerL.z;

	/*FRotator temp = lowerArmL->Rotator();
	temp.Yaw *= -1;
	FQuat tempq = temp.Quaternion();
	lowerArmL->W = tempq.W;
	lowerArmL->X = tempq.X;
	lowerArmL->Y = tempq.Y;
	lowerArmL->Z = tempq.Z;*/

	upperArmR->W = inRotUpperR.w;
	upperArmR->X = inRotUpperR.x;
	upperArmR->Y = inRotUpperR.y;
	upperArmR->Z = inRotUpperR.z;

	lowerArmR->W = inRotLowerR.w;
	lowerArmR->X = inRotLowerR.x;
	lowerArmR->Y = inRotLowerR.y;
	lowerArmR->Z = inRotLowerR.z;
}
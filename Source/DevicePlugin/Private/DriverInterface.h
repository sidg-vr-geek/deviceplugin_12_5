#pragma once

#ifndef _DRIVERINTERFACE_H_
#define _DRIVERINTERFACE_H_

#include "DeviceDriver.h"

class CLSDRVIFACE
{
private:
	bool	bInit;

public:
	CLSDRVIFACE::CLSDRVIFACE();

	void		GetCurrentRotation(FQuat *upperArmL, FQuat *lowerArmL, FQuat *upperArmR, FQuat *lowerArmR);
	void		InitDriver();

	bool		IsInit();
};

#endif
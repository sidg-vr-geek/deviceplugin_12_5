#pragma once

#include "StructQuat.h"

namespace NmspDevDrv
{
	class CLSDEVDRV
	{
	public :
		// Driver initialization...
		static void DrvInit();

		// Function to print rot data
		static void DrvGetRawQuat(STQUAT *upperArmL, STQUAT *lowerArmL, STQUAT *upperArmR, STQUAT *lowerArmR);
	};

}

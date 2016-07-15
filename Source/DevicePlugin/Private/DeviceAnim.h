#pragma once

#include "DeviceAnim.generated.h"

UCLASS()
class MDEVICEPLUGIN_API UDeviceAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	int a;
	// Called every frame
	virtual void NativeInitializeAnimation() override;

	// Called every frame
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
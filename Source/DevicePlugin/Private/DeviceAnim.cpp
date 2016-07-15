#include "DevicePluginPrivatePCH.h"
#include "DeviceAnim.h"

// Called on Post init
void UDeviceAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	UE_LOG(LogTemp, Warning, TEXT("Init Animation"));
	//SC_upperArmRot = FRotator(0, 0, 0);
}

// Called every frame
void UDeviceAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}
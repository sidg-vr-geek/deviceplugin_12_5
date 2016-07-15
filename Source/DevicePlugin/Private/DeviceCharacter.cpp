// Fill out your copyright notice in the Description page of Project Settings.

#include "DevicePluginPrivatePCH.h"
#include "DeviceCharacter.h"

// Sets default values
ADeviceCharacter::ADeviceCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	UCameraComponent* playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	visiblePlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player's Skeletal Mesh"));
	poseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Poseable Mesh"));
	visiblePlayerMesh->AttachTo(RootComponent);
	playerCamera->AttachTo(RootComponent);
	//playerCamera->SetRelativeLocation(CameraLocation);
	//playerCamera->SetRelativeRotation(CameraRotation);
	playerCamera->SetRelativeLocation(FVector(-0.0f, 0.0f, 0.0f));
	playerCamera->SetRelativeRotation(FRotator(-0.0f, 0.0f, 0.0f));

	//body.arms.left.upper.rotationQuat = { 0.0 };
	//body.arms.left.lower.rotationQuat = { 0.0 };
}

// Called when the game starts or when spawned
void ADeviceCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeviceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FQuat upperArmLQuat, lowerArmLQuat, upperArmRQuat, lowerArmRQuat;

	if (IDevicePlugin::IsAvailable())
	{
		IDevicePlugin::Get().GetCurrentRotation(&upperArmLQuat, &lowerArmLQuat, &upperArmRQuat, &lowerArmRQuat);

		//body.arms.left.upper.rotation.Pitch  += 1;
		//body.arms.left.lower.rotation.Pitch += 2;
		//body.arms.right.upper.rotation.Pitch += 1;
		//body.arms.right.lower.rotation.Pitch += 2;
		body.arms.left.upper.rotation = upperArmLQuat.Rotator();
		body.arms.left.lower.rotation = lowerArmLQuat.Rotator();
		body.arms.right.upper.rotation = upperArmRQuat.Rotator();
		body.arms.right.lower.rotation = lowerArmRQuat.Rotator();

		UE_LOG(LogTemp, Warning, TEXT("UpperArmL. Yaw = %f, Pitch = %f, Roll = %f\n"),
			body.arms.left.lower.rotation.Yaw,
			body.arms.left.lower.rotation.Pitch,
			body.arms.left.lower.rotation.Roll);

		UE_LOG(LogTemp, Warning, TEXT("UpperArmR. Yaw = %f, Pitch = %f, Roll = %f\n"),
			body.arms.right.lower.rotation.Yaw,
			body.arms.right.lower.rotation.Pitch,
			body.arms.right.lower.rotation.Roll);

		/*FQuat tempQuat;
		tempQuat = body.arms.left.upper.rotation.Quaternion();
		tempQuat = body.arms.left.lower.rotation.Quaternion();
		UE_LOG(LogTemp, Warning, TEXT("LowerArmL. W = %f, X = %f, Y = %f, Z = %f"),
		tempQuat.W,
		tempQuat.X,
		tempQuat.Y,
		tempQuat.Z);
		tempQuat = body.arms.right.upper.rotation.Quaternion();
		UE_LOG(LogTemp, Warning, TEXT("UpperArmR. W = %f, X = %f, Y = %f, Z = %f"),
		tempQuat.W,
		tempQuat.X,
		tempQuat.Y,
		tempQuat.Z);
		tempQuat = body.arms.right.lower.rotation.Quaternion();
		UE_LOG(LogTemp, Warning, TEXT("LowerArmR. W = %f, X = %f, Y = %f, Z = %f"),
		tempQuat.W,
		tempQuat.X,
		tempQuat.Y,
		tempQuat.Z);*/
	}
}

F_BODY ADeviceCharacter::GetBodyPosture()
{
	return body;
}

// Called to bind functionality to input
void ADeviceCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("RecalibrateDevice", IE_Released, this, &ADeviceCharacter::RecalibrateDevice);
	InputComponent->BindAction("UpperL", IE_Released, this, &ADeviceCharacter::UECalibUpperL);
	InputComponent->BindAction("LowerL", IE_Released, this, &ADeviceCharacter::UECalibLowerL);
	InputComponent->BindAction("UpperR", IE_Released, this, &ADeviceCharacter::UECalibUpperR);
	InputComponent->BindAction("LowerR", IE_Released, this, &ADeviceCharacter::UECalibLowerR);
}

void ADeviceCharacter::UECalibUpperL()
{
	if (IDevicePlugin::IsAvailable())
	{
		IDevicePlugin::Get().UECalib(0);
	}
}

void ADeviceCharacter::UECalibLowerL()
{
	if (IDevicePlugin::IsAvailable())
	{
		IDevicePlugin::Get().UECalib(1);
	}
}

void ADeviceCharacter::UECalibUpperR()
{
	if (IDevicePlugin::IsAvailable())
	{
		IDevicePlugin::Get().UECalib(2);
	}
}

void ADeviceCharacter::UECalibLowerR()
{
	if (IDevicePlugin::IsAvailable())
	{
		IDevicePlugin::Get().UECalib(3);
	}
}

void ADeviceCharacter::RecalibrateDevice()
{
	if (IDevicePlugin::IsAvailable())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Starting recalibration..."));
		IDevicePlugin::Get().RecalibrateDevice();
		//UE_LOG(LogTemp, Warning, TEXT("Recalibration Done..."));
	}
}
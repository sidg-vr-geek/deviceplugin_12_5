// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "StructBody.h"
#include "DeviceAnim.h"
#include "DeviceCharacter.generated.h"

UCLASS()
class MDEVICEPLUGIN_API ADeviceCharacter : public ACharacter
{
	GENERATED_BODY()

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skel Controls")
		F_BODY		body;
	// Sets default values for this character's properties
	ADeviceCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void UECalibUpperL();
	void UECalibLowerL();
	void UECalibUpperR();
	void UECalibLowerR();

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* visiblePlayerMesh;

	UPROPERTY(EditAnywhere)
		UPoseableMeshComponent* poseableMesh;

	UPROPERTY(EditAnywhere)
		UDeviceAnim* animInstance;

	UPROPERTY(EditAnywhere, Category = "Camera Properties")
		FVector CameraLocation;

	UPROPERTY(EditAnywhere, Category = "Camera Properties")
		FRotator CameraRotation;

	void RecalibrateDevice();

	F_BODY GetBodyPosture();
};
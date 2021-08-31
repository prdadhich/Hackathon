// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/TriggerVolume.h"
#include "MoveCamera.generated.h"

UCLASS()
class HACKATHON_API AMoveCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:


	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* PlayerCamera;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Player;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* PlayerCapsule;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringComponent;

protected: 
	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* SculptureOneTrigger;

private:
	UFUNCTION()
	void Move();
	UFUNCTION()
	void MoveRight();
	UFUNCTION()
	void Rotate();
	UFUNCTION()
	void RotateUp();

	UFUNCTION()
	void CalculateMoveInput( float throttle);
	UFUNCTION()
	void CalculateRotationInput(float throttle);
	UFUNCTION()
	void CalculateRotationInputUp(float throttle);
	UFUNCTION()
	void CalculateMoveInputRight(float throttle);

private: 
	FVector MoveDirection;
	FVector MoveDirectionRight;
	FQuat RotationDirection;
	FQuat RotationDirectionUp;
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
	float RotateSpeedUp = 100.0f;

	bool isOverlapping = false;
	int count = 0;
};

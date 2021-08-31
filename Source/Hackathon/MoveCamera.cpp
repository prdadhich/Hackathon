// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveCamera.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMoveCamera::AMoveCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	RootComponent= PlayerCapsule;

	SpringComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComponent"));
	SpringComponent->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringComponent);
	

}

// Called when the game starts or when spawned
void AMoveCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMoveCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	//RotateUp();
	Move();
	MoveRight();
	PlayerCamera->AddLocalRotation(RotationDirectionUp,true);
	


	isOverlapping = PlayerCapsule->IsOverlappingComponent(SculptureOneTrigger);
	if (isOverlapping)
	{
		UE_LOG(LogTemp,Warning,TEXT("Overalpping"));
	}

}

// Called to bind functionality to input
void AMoveCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMoveCamera::CalculateMoveInput);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMoveCamera::CalculateMoveInputRight);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMoveCamera::CalculateRotationInput);
	PlayerInputComponent->BindAxis(TEXT("RotateUp"), this, &AMoveCamera::CalculateRotationInputUp);
	
}

void AMoveCamera::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void AMoveCamera::MoveRight()
{
	AddActorLocalOffset(MoveDirectionRight, true);
}



void AMoveCamera::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}
void AMoveCamera::RotateUp()
{
	AddActorLocalRotation(RotationDirectionUp, true);
}
	
void AMoveCamera::CalculateMoveInput(float throttle)
{
	MoveDirection = FVector(throttle * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
	
}

void AMoveCamera::CalculateRotationInput(float throttle)
{
	float RotateAmount = (throttle * RotateSpeed * GetWorld()->DeltaTimeSeconds);
	FRotator Rotation = FRotator(0,RotateAmount,0);
	RotationDirection = FQuat(Rotation);
}
void AMoveCamera::CalculateRotationInputUp(float throttle)
{
	float RotateAmount = (throttle * RotateSpeed * GetWorld()->DeltaTimeSeconds);
	FRotator Rotation = FRotator(RotateAmount,0,0);
	RotationDirectionUp = FQuat(Rotation);
}

void AMoveCamera::CalculateMoveInputRight(float throttle)
{
	MoveDirectionRight = FVector(0, (throttle * MoveSpeed * GetWorld()->DeltaTimeSeconds), 0);

}


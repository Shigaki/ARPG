// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "..\Public\ARPGPlayer.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AARPGPlayer::AARPGPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	ClothMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ClothMesh");
	BootsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BootsMesh");
	MaskMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MaskMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//RootComponent = CapsuleComponent;
	//	Mesh->SetupAttachment(CapsuleComponent);
	RootComponent = Mesh;
	ClothMesh->SetupAttachment(Mesh);
	BootsMesh->SetupAttachment(Mesh);
	MaskMesh->SetupAttachment(Mesh);
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	//Camera->SetWorldLocation(FVector(-350.f, 0.f, 500.f));
	//Camera->SetRelativeRotation(FRotator(0.f, 60.f, 0.f));

}

// Called when the game starts or when spawned
void AARPGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARPGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &AARPGPlayer::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &AARPGPlayer::MoveForward);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AARPGPlayer::Jump);

}

void AARPGPlayer::MoveRight(float Value) {
	/*
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *Right.ToString());
	AddMovementInput(Right);
	*/
	if (Value != 0.f) {
		const FRotator ControlDirection = GetControlRotation();
		const FRotator YawDirection = FRotator(0, ControlDirection.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::X);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s; Value: %f"), *Direction.ToString(), Value);
		AddMovementInput(Direction, Value);
	}
}
void AARPGPlayer::MoveForward(float Value) {
	/*
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *Forward.ToString());
	AddMovementInput(Forward);
	*/
	if (Value != 0.f) {
		const FRotator ControlDirection = GetControlRotation();
		const FRotator YawDirection = FRotator(0, ControlDirection.Yaw, 0);
		const FVector Direction = -FRotationMatrix(YawDirection).GetUnitAxis(EAxis::Y);
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s; Value: %f"), *Direction.ToString(), Value);
		AddMovementInput(Direction, Value);
	}
}
void AARPGPlayer::Jump() {
	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
}

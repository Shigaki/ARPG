// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include <ARPG/Public/ARPGHealthComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

// Sets default values
AARPGPlayer::AARPGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UARPGHealthComponent>(TEXT("HealthComponent"));

	// Camera Settings
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(this->GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 1200.f;
	SpringArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	// Mesh Settings
	USkeletalMeshComponent* MeshRoot = this->GetMesh();
	MeshRoot->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -110.f), FRotator(0.f, -90.f, 0.f));

	ClothMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClothMesh"));
	BootsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BootsMesh"));
	MaskMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MaskMesh"));

	ClothMesh->SetupAttachment(MeshRoot);
	BootsMesh->SetupAttachment(MeshRoot);
	MaskMesh->SetupAttachment(MeshRoot);

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

	// Input Binding
	InputComponent->BindAxis("MoveForward", this, &AARPGPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AARPGPlayer::MoveRight);
}

void AARPGPlayer::MoveForward(float Value)
{
	if (Value != 0.f) {
		const FVector Forward = Camera->GetForwardVector() * MoveSpeed * Value;
		//UE_LOG(LogTemp, Warning, TEXT("Move Value: %s %f"), *Forward.ToString());
		AddMovementInput(Forward);
	}
}

void AARPGPlayer::MoveRight(float Value)
{
	if (Value != 0.f) {
		const FVector Right = Camera->GetRightVector() * MoveSpeed * Value;
		//UE_LOG(LogTemp, Warning, TEXT("Move Value: %s %f"), *Right.ToString());
		AddMovementInput(Right);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGPlayer.generated.h"

class UARPGHealthComponent;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class ARPG_API AARPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UARPGHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* ClothMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* BootsMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* MaskMesh;

	void MoveRight(float Value);
	void MoveForward(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 500.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};

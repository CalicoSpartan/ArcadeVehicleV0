// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Vehicle.generated.h"

UCLASS()
class ARCADEVEHICLEV0_API AVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicle();

	UPROPERTY(EditAnywhere)
		UBoxComponent* Collider;
	UPROPERTY(EditAnywhere)
		USceneComponent* FrontLeftSpring;
	UPROPERTY(EditAnywhere)
		USceneComponent* FrontRightSpring;
	UPROPERTY(EditAnywhere)
		USceneComponent* BackLeftSpring;
	UPROPERTY(EditAnywhere)
		USceneComponent* BackRightSpring;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};

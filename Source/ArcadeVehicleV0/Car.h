// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine.h"
#include "Wheel.h"
#include "Components/BoxComponent.h"
#include "Car.generated.h"

UCLASS()
class ARCADEVEHICLEV0_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

	UPROPERTY(EditAnywhere)
		TArray<class UWheel*> Wheels;
	UPROPERTY(EditAnywhere)
		class UWheel* Wheel1;
	UPROPERTY(EditAnywhere)
		class UWheel* Wheel2;
	UPROPERTY(EditAnywhere)
		class UWheel* Wheel3;
	UPROPERTY(EditAnywhere)
		class UWheel* Wheel4;

	UPROPERTY(EditAnywhere)
		UCameraComponent* MyCamera;

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
	UPROPERTY(EditAnywhere)
		FHitResult FL_Hit;
	UPROPERTY(EditAnywhere)
		FHitResult FR_Hit;
	UPROPERTY(EditAnywhere)
		FHitResult BL_Hit;
	UPROPERTY(EditAnywhere)
		FHitResult BR_Hit;



	UPROPERTY(EditAnywhere)
		float FL_SpringForce;
	UPROPERTY(EditAnywhere)
		float FL_DamperForce;
	UPROPERTY(EditAnywhere)
		float FL_SpringConstant;
	UPROPERTY(EditAnywhere)
		float FL_DamperConstant;
	UPROPERTY(EditAnywhere)
		float FL_RestLength;
	UPROPERTY(EditAnywhere)
		float FL_PreviousLength;
	UPROPERTY(EditAnywhere)
		float FL_CurrentLength;
	UPROPERTY(EditAnywhere)
		float FL_SpringVelocity;






	UPROPERTY(EditAnywhere)
		float FR_SpringForce;
	UPROPERTY(EditAnywhere)
		float FR_DamperForce;
	UPROPERTY(EditAnywhere)
		float FR_SpringConstant;
	UPROPERTY(EditAnywhere)
		float FR_DamperConstant;
	UPROPERTY(EditAnywhere)
		float FR_RestLength;
	UPROPERTY(EditAnywhere)
		float FR_PreviousLength;
	UPROPERTY(EditAnywhere)
		float FR_CurrentLength;
	UPROPERTY(EditAnywhere)
		float FR_SpringVelocity;


	UPROPERTY(EditAnywhere)
		float BR_SpringForce;
	UPROPERTY(EditAnywhere)
		float BR_DamperForce;
	UPROPERTY(EditAnywhere)
		float BR_SpringConstant;
	UPROPERTY(EditAnywhere)
		float BR_DamperConstant;
	UPROPERTY(EditAnywhere)
		float BR_RestLength;
	UPROPERTY(EditAnywhere)
		float BR_PreviousLength;
	UPROPERTY(EditAnywhere)
		float BR_CurrentLength;
	UPROPERTY(EditAnywhere)
		float BR_SpringVelocity;



	UPROPERTY(EditAnywhere)
		float BL_SpringForce;
	UPROPERTY(EditAnywhere)
		float BL_DamperForce;
	UPROPERTY(EditAnywhere)
		float BL_SpringConstant;
	UPROPERTY(EditAnywhere)
		float BL_DamperConstant;
	UPROPERTY(EditAnywhere)
		float BL_RestLength;
	UPROPERTY(EditAnywhere)
		float BL_PreviousLength;
	UPROPERTY(EditAnywhere)
		float BL_CurrentLength;
	UPROPERTY(EditAnywhere)
		float BL_SpringVelocity;



	UPROPERTY(EditAnywhere, Category = "Wheel")
		float WheelRadius;


	UPROPERTY(EditAnywhere, Category = "Suspension")
		float SuspensionLength;
	UPROPERTY(EditAnywhere, Category = "Suspension")
		float SuspensionForceMultiplier;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};

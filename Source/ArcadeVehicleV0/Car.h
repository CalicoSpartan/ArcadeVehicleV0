// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
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
		UBoxComponent* Collider;
	UPROPERTY(EditAnywhere,Category = "FrontLeft")
		USceneComponent* FrontLeftSpring;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		USceneComponent* FrontRightSpring;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		USceneComponent* BackLeftSpring;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		USceneComponent* BackRightSpring;
	UPROPERTY(EditAnywhere, Category = "Handling")
		USceneComponent* CarThrottleForceLocation;
	UPROPERTY(EditAnywhere, Category = "Handling")
		USceneComponent* COMcomponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		FHitResult FL_Hit;
	UPROPERTY(EditAnywhere,Category = "FrontRight")
		FHitResult FR_Hit;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		FHitResult BL_Hit;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		FHitResult BR_Hit;



	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_SpringForce;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_DamperForce;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_SpringConstant;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_DamperConstant;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_RestLength;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_PreviousLength;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_CurrentLength;
	UPROPERTY(EditAnywhere, Category = "FrontLeft")
		float FL_SpringVelocity;






	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_SpringForce;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_DamperForce;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_SpringConstant;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_DamperConstant;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_RestLength;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_PreviousLength;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_CurrentLength;
	UPROPERTY(EditAnywhere, Category = "FrontRight")
		float FR_SpringVelocity;


	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_SpringForce;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_DamperForce;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_SpringConstant;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_DamperConstant;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_RestLength;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_PreviousLength;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_CurrentLength;
	UPROPERTY(EditAnywhere, Category = "BackRight")
		float BR_SpringVelocity;



	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_SpringForce;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_DamperForce;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_SpringConstant;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_DamperConstant;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_RestLength;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_PreviousLength;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_CurrentLength;
	UPROPERTY(EditAnywhere, Category = "BackLeft")
		float BL_SpringVelocity;



	UPROPERTY(EditAnywhere, Category = "Wheel")
		float WheelRadius;
	UPROPERTY(EditAnywhere, Category = "Speed")
		float AccelForce = 20000.0f;
	UPROPERTY(EditAnywhere, Category = "Speed")
		float DecelForce = 20000.0f;
	UPROPERTY(EditAnywhere, Category = "Speed")
		float TurnForce = 20000.0f;
	UPROPERTY(EditAnywhere, Category = "Handling")
		float FrictionForce = 2000.0f;
	UPROPERTY(EditAnywhere, Category = "Handling")
		float DriveFriction = 2000.0f;
	UPROPERTY(EditAnywhere, Category = "Handling")
		float HandBrakeFriction = 2000.0f;
	UPROPERTY(EditAnywhere, Category = "Handling")
		float BASEAngularDamping = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Handling")
		float TURNAngularDamping = 0.5f;
	UPROPERTY(EditAnywhere)
		bool IsAccelerating = false;
	UPROPERTY(EditAnywhere)
		bool IsGrounded = false;
	UPROPERTY(EditAnywhere)
		bool IsTurning = false;
	UPROPERTY(EditAnywhere)
		bool bUsingHandBrake = false;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void Accelerate(float Value);
	UFUNCTION()
		void Decelerate(float Value);
	UFUNCTION()
		void Turn(float Value);
	UFUNCTION()
		void ApplyHandBrake();
	UFUNCTION()
		void ReleaseHandBrake();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};

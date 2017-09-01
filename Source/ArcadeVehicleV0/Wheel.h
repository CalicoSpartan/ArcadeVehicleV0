// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "Components/ActorComponent.h"
#include "Wheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADEVEHICLEV0_API UWheel : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheel();

	//UPROPERTY(EditAnywhere)
	//	USceneComponent* MyRoot

	UPROPERTY(VisibleAnywhere)
		FHitResult GroundCheck;

	UPROPERTY(EditAnywhere)
		class ACar* Car;
	UPROPERTY(EditAnywhere)
		USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
		float SpringForce = 0.0f;
	UPROPERTY(EditAnywhere)
		float DamperForce = 0.0f;
	UPROPERTY(EditAnywhere)
		float SpringConstant = 3000.0f;
	UPROPERTY(EditAnywhere)
		float DamperConstant = 300.0f;
	UPROPERTY(EditAnywhere)
		float RestLength = 0.5f;
	UPROPERTY(EditAnywhere)
		float PreviousLength = 0.0f;
	UPROPERTY(EditAnywhere)
		float CurrentLength = 0.0f;
	UPROPERTY(EditAnywhere)
		float SpringVelocity = 0.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

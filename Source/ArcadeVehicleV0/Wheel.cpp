// Fill out your copyright notice in the Description page of Project Settings.

#include "Wheel.h"


// Sets default values for this component's properties
UWheel::UWheel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	

	// ...
}


// Called when the game starts
void UWheel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWheel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Car != NULL)
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Car);
		if (GetWorld()->LineTraceSingleByChannel(GroundCheck,MyRoot->GetComponentLocation(), MyRoot->GetComponentLocation() + Car->GetActorUpVector() * -(RestLength + Car->WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
		{
			//DrawDebugLine(GetWorld(), GetComponentLocation(), GetComponentLocation() + Car->GetActorUpVector(), FColor::Red, false, 1.0f);

			PreviousLength = CurrentLength;
			CurrentLength = RestLength - (GroundCheck.Distance - Car->WheelRadius);
			SpringVelocity = (CurrentLength - PreviousLength) / DeltaTime;
			SpringForce = SpringConstant * CurrentLength;
			DamperForce = DamperConstant * SpringVelocity;
			Car->Collider->AddForceAtLocation(Car->GetActorUpVector() * SpringForce + DamperForce, MyRoot->GetComponentLocation());
		}
	}
}


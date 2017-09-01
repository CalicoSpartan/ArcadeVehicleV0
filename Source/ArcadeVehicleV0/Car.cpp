// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"


// Sets default values
ACar::ACar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(Collider);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	FrontLeftSpring = CreateDefaultSubobject<USceneComponent>(TEXT("FrontLeftSpring"));
	FrontLeftSpring->SetupAttachment(Collider);

	FrontRightSpring = CreateDefaultSubobject<USceneComponent>(TEXT("FrontRightSpring"));
	FrontRightSpring->SetupAttachment(Collider);

	BackLeftSpring = CreateDefaultSubobject<USceneComponent>(TEXT("BackLeftSpring"));
	BackLeftSpring->SetupAttachment(Collider);

	BackRightSpring = CreateDefaultSubobject<USceneComponent>(TEXT("BackRightSpring"));
	BackRightSpring->SetupAttachment(Collider);

	Wheel1 = CreateDefaultSubobject<UWheel>(TEXT("Wheel1"));
	Wheel1->MyRoot->SetupAttachment(FrontLeftSpring);
	Wheel1->MyRoot->SetWorldLocation(FrontLeftSpring->GetComponentLocation());
	Wheel2 = CreateDefaultSubobject<UWheel>(TEXT("Wheel2"));
	Wheel2->MyRoot->SetupAttachment(FrontRightSpring);
	Wheel2->MyRoot->SetWorldLocation(FrontRightSpring->GetComponentLocation());
	Wheel3 = CreateDefaultSubobject<UWheel>(TEXT("Wheel3"));
	Wheel3->MyRoot->SetupAttachment(BackLeftSpring);
	Wheel3->MyRoot->SetWorldLocation(BackLeftSpring->GetComponentLocation());
	Wheel4 = CreateDefaultSubobject<UWheel>(TEXT("Wheel4"));
	Wheel4->MyRoot->SetupAttachment(BackRightSpring);
	Wheel4->MyRoot->SetWorldLocation(BackRightSpring->GetComponentLocation());
	//Wheels.Add(Wheel1);
	//Wheels.Add(Wheel2);
	//Wheels.Add(Wheel3);
	//Wheels.Add(Wheel4);

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	Collider->SetSimulatePhysics(true);
	Wheels.Add(Wheel1);
	Wheels.Add(Wheel2);
	Wheels.Add(Wheel3);
	Wheels.Add(Wheel4);

	for (int32 i = 0; i < Wheels.Num(); ++i)
	{
		if (UWheel* wheel = Cast<UWheel>(Wheels[i]))
		{
			//wheel->Car = this;
		}
	}


}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(FL_Hit, FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -(FL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	DrawDebugLine(GetWorld(), FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);

	FL_PreviousLength = FL_CurrentLength;
	FL_CurrentLength = FL_RestLength - (FL_Hit.Distance - WheelRadius);
	FL_SpringVelocity = (FL_CurrentLength - FL_PreviousLength) / DeltaTime;
	FL_SpringForce = FL_SpringConstant * FL_CurrentLength;
	FL_DamperForce = FL_DamperConstant * FL_SpringVelocity;
	Collider->AddForceAtLocation(GetActorUpVector() * FL_SpringForce + FL_DamperForce, FrontLeftSpring->GetComponentLocation());


	}
	if (GetWorld()->LineTraceSingleByChannel(FR_Hit, FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -(FR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	DrawDebugLine(GetWorld(), FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);
	FR_PreviousLength = FR_CurrentLength;
	FR_CurrentLength = FR_RestLength - (FR_Hit.Distance - WheelRadius);
	FR_SpringVelocity = (FR_CurrentLength - FR_PreviousLength) / DeltaTime;
	FR_SpringForce = FR_SpringConstant * FR_CurrentLength;
	FR_DamperForce = FR_DamperConstant * FR_SpringVelocity;
	Collider->AddForceAtLocation(GetActorUpVector() * FR_SpringForce + FR_DamperForce,FrontRightSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BL_Hit, BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -(BL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	DrawDebugLine(GetWorld(), BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);

	BL_PreviousLength = BL_CurrentLength;
	BL_CurrentLength = BL_RestLength - (BL_Hit.Distance - WheelRadius);
	BL_SpringVelocity = (BL_CurrentLength - BL_PreviousLength) / DeltaTime;
	BL_SpringForce = BL_SpringConstant * BL_CurrentLength;
	BL_DamperForce = BL_DamperConstant * BL_SpringVelocity;
	Collider->AddForceAtLocation(GetActorUpVector() * BL_SpringForce + BL_DamperForce, BackLeftSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BR_Hit, BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -(BR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	DrawDebugLine(GetWorld(), BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);

	BR_PreviousLength = BR_CurrentLength;
	BR_CurrentLength = BR_RestLength - (BR_Hit.Distance - WheelRadius);
	BR_SpringVelocity = (BR_CurrentLength - BR_PreviousLength) / DeltaTime;
	BR_SpringForce = BR_SpringConstant * BR_CurrentLength;
	BR_DamperForce = BR_DamperConstant * BR_SpringVelocity;
	Collider->AddForceAtLocation(GetActorUpVector() * BR_SpringForce + BR_DamperForce, BackRightSpring->GetComponentLocation());
	}
	*/
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


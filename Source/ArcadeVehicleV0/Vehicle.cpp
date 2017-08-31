// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle.h"


// Sets default values
AVehicle::AVehicle()
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
	
	
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	Collider->SetSimulatePhysics(true);
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(FL_Hit, FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		DrawDebugLine(GetWorld(), FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);
	}
	if (GetWorld()->LineTraceSingleByChannel(FR_Hit, FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		DrawDebugLine(GetWorld(), FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);
	}

	if (GetWorld()->LineTraceSingleByChannel(BL_Hit, BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		DrawDebugLine(GetWorld(), BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);
	}

	if (GetWorld()->LineTraceSingleByChannel(BR_Hit, BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		DrawDebugLine(GetWorld(), BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -SuspensionLength, FColor::Red, false, 1.0f);
	}
}

// Called to bind functionality to input
void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


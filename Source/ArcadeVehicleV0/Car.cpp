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



}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	Collider->SetSimulatePhysics(true);



}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(FL_Hit, FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -(FL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	
		
		FL_PreviousLength = FL_CurrentLength;
		FL_CurrentLength = FL_RestLength - (FL_Hit.Distance - WheelRadius);
		FL_SpringVelocity = (FL_CurrentLength - FL_PreviousLength) / DeltaTime;
		FL_SpringForce = FL_SpringConstant * FL_CurrentLength;
		FL_DamperForce = FL_DamperConstant * FL_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * FL_SpringForce + FL_DamperForce, FrontLeftSpring->GetComponentLocation());


	}
	if (GetWorld()->LineTraceSingleByChannel(FR_Hit, FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -(FR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	
		FR_PreviousLength = FR_CurrentLength;
		FR_CurrentLength = FR_RestLength - (FR_Hit.Distance - WheelRadius);
		FR_SpringVelocity = (FR_CurrentLength - FR_PreviousLength) / DeltaTime;
		FR_SpringForce = FR_SpringConstant * FR_CurrentLength;
		FR_DamperForce = FR_DamperConstant * FR_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * FR_SpringForce + FR_DamperForce,FrontRightSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BL_Hit, BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -(BL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	

		BL_PreviousLength = BL_CurrentLength;
		BL_CurrentLength = BL_RestLength - (BL_Hit.Distance - WheelRadius);
		BL_SpringVelocity = (BL_CurrentLength - BL_PreviousLength) / DeltaTime;
		BL_SpringForce = BL_SpringConstant * BL_CurrentLength;
		BL_DamperForce = BL_DamperConstant * BL_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * BL_SpringForce + BL_DamperForce, BackLeftSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BR_Hit, BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -(BR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	

		BR_PreviousLength = BR_CurrentLength;
		BR_CurrentLength = BR_RestLength - (BR_Hit.Distance - WheelRadius);
		BR_SpringVelocity = (BR_CurrentLength - BR_PreviousLength) / DeltaTime;
		BR_SpringForce = BR_SpringConstant * BR_CurrentLength;
		BR_DamperForce = BR_DamperConstant * BR_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * BR_SpringForce + BR_DamperForce, BackRightSpring->GetComponentLocation());
	}
	
}

void ACar::Decelerate(float Value)
{
	if (FL_Hit.ImpactNormal != FVector::ZeroVector)
	{
		
		FVector SurfaceDirection = UKismetMathLibrary::ProjectVectorOnToPlane(GetActorForwardVector(), FL_Hit.ImpactNormal).GetSafeNormal();
		Collider->AddForceAtLocation(-SurfaceDirection * DecelForce * Value, Collider->GetCenterOfMass());
	}
	//FVector dir = UKismetMathLibrary::ProjectVectorOnToVector(GetActorForwardVector(), FL_Hit.Normal);
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + dir * 1000.0f, FColor::Red, false, 3.0f);

}
void ACar::Accelerate(float Value)
{
	if (FL_Hit.ImpactNormal != FVector::ZeroVector)
	{
		
		FVector SurfaceDirection = UKismetMathLibrary::ProjectVectorOnToPlane(GetActorForwardVector(), FL_Hit.ImpactNormal).GetSafeNormal();
		Collider->AddForceAtLocation(SurfaceDirection * AccelForce * Value, Collider->GetCenterOfMass());
		//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + CrossDir, FColor::Red, false, 3.0f);
		//UE_LOG(LogClass, Log, TEXT("Dir: %s"),*dir.ToString());
		//UE_LOG(LogClass, Log, TEXT("AxisValue: %f"),Value);
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Throttle", this, &ACar::Accelerate);
	PlayerInputComponent->BindAxis("Brake", this, &ACar::Decelerate);
}


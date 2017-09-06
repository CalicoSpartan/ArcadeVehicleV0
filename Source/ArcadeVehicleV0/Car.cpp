// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"


// Sets default values
ACar::ACar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	Collider->SetAngularDamping(BASEAngularDamping);



	FrontLeftSpring = CreateDefaultSubobject<USceneComponent>(TEXT("FrontLeftSpring"));
	FrontLeftSpring->SetupAttachment(Collider);

	FrontRightSpring = CreateDefaultSubobject<USceneComponent>(TEXT("FrontRightSpring"));
	FrontRightSpring->SetupAttachment(Collider);

	BackLeftSpring = CreateDefaultSubobject<USceneComponent>(TEXT("BackLeftSpring"));
	BackLeftSpring->SetupAttachment(Collider);

	BackRightSpring = CreateDefaultSubobject<USceneComponent>(TEXT("BackRightSpring"));
	BackRightSpring->SetupAttachment(Collider);
	CarThrottleForceLocation = CreateDefaultSubobject<USceneComponent>(TEXT("CarThrottleForceLocation"));
	CarThrottleForceLocation->SetupAttachment(Collider);
	COMcomponent = CreateDefaultSubobject<USceneComponent>(TEXT("COMcomponent"));
	COMcomponent->SetupAttachment(Collider);
	Collider->SetCenterOfMass(COMcomponent->GetComponentLocation());
	FrictionForce = DriveFriction;


}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->SetSimulatePhysics(true);
	FrictionForce = DriveFriction;
	




}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = GetActorRotation();
	FVector vel = rot.UnrotateVector(GetVelocity());
	CurrentForwardSpeed = vel.X / SpeedDivisionScale;
	//UE_LOG(LogClass, Log, TEXT("Speed: %f"), CurrentForwardSpeed);
	
	IsGrounded = false;
	CurrentSpeed = GetVelocity().Size() / SpeedDivisionScale;
	TurnToSpeedPercentage = CurrentSpeed * TurnToSpeed;
	TurnStrengthPercentage = 1.0f - CurrentSpeed / MaxSpeed;
	DriftToSpeedPercentage = CurrentSpeed * DriftToSpeed;
	DriftStrengthPercentage = 1.0f - CurrentSpeed / MaxSpeed;
	
	//if (TurnStrengthPercentage <= 0.15f)
	//{
	//	TurnStrengthPercentage = 0.15f;
	//}
	/*
	if (FPlatformMath::RoundToFloat(TurnStrengthPercentage) == 0.0f)
	{
		TurnStrengthPercentage = 0.0f;
	}
	*/
	//Collider->AddImpulse(test * FrictionForce);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(FL_Hit, FrontLeftSpring->GetComponentLocation(), FrontLeftSpring->GetComponentLocation() + GetActorUpVector() * -(FL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	
		IsGrounded = true;
		FL_PreviousLength = FL_CurrentLength;
		FL_CurrentLength = FL_RestLength - (FL_Hit.Distance - WheelRadius);
		FL_SpringVelocity = (FL_CurrentLength - FL_PreviousLength) / DeltaTime;
		FL_SpringForce = FL_SpringConstant * FL_CurrentLength;
		FL_DamperForce = FL_DamperConstant * FL_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * FL_SpringForce + FL_DamperForce, FrontLeftSpring->GetComponentLocation());


	}
	if (GetWorld()->LineTraceSingleByChannel(FR_Hit, FrontRightSpring->GetComponentLocation(), FrontRightSpring->GetComponentLocation() + GetActorUpVector() * -(FR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
		IsGrounded = true;
		FR_PreviousLength = FR_CurrentLength;
		FR_CurrentLength = FR_RestLength - (FR_Hit.Distance - WheelRadius);
		FR_SpringVelocity = (FR_CurrentLength - FR_PreviousLength) / DeltaTime;
		FR_SpringForce = FR_SpringConstant * FR_CurrentLength;
		FR_DamperForce = FR_DamperConstant * FR_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * FR_SpringForce + FR_DamperForce,FrontRightSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BL_Hit, BackLeftSpring->GetComponentLocation(), BackLeftSpring->GetComponentLocation() + GetActorUpVector() * -(BL_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	
		IsGrounded = true;
		BL_PreviousLength = BL_CurrentLength;
		BL_CurrentLength = BL_RestLength - (BL_Hit.Distance - WheelRadius);
		BL_SpringVelocity = (BL_CurrentLength - BL_PreviousLength) / DeltaTime;
		BL_SpringForce = BL_SpringConstant * BL_CurrentLength;
		BL_DamperForce = BL_DamperConstant * BL_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * BL_SpringForce + BL_DamperForce, BackLeftSpring->GetComponentLocation());

	}

	if (GetWorld()->LineTraceSingleByChannel(BR_Hit, BackRightSpring->GetComponentLocation(), BackRightSpring->GetComponentLocation() + GetActorUpVector() * -(BR_RestLength + WheelRadius), ECollisionChannel::ECC_Visibility, QueryParams))
	{
	
		IsGrounded = true;
		BR_PreviousLength = BR_CurrentLength;
		BR_CurrentLength = BR_RestLength - (BR_Hit.Distance - WheelRadius);
		BR_SpringVelocity = (BR_CurrentLength - BR_PreviousLength) / DeltaTime;
		BR_SpringForce = BR_SpringConstant * BR_CurrentLength;
		BR_DamperForce = BR_DamperConstant * BR_SpringVelocity;
		Collider->AddForceAtLocation(GetActorUpVector() * BR_SpringForce + BR_DamperForce, BackRightSpring->GetComponentLocation());
	}
	


	if (IsGrounded == true)
	{
		

		//FVector test = UKismetMathLibrary::ProjectVectorOnToVector(GetVelocity().GetSafeNormal(), GetActorRightVector()).GetSafeNormal();
		float DotProduct = -1.0f * FrictionForce * FVector::DotProduct(GetActorRightVector(), GetVelocity());
		UE_LOG(LogClass, Log, TEXT("DotProduct:  %f"), FVector::DotProduct(GetActorRightVector(), GetVelocity()));
		//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + test, FColor::Red, false, 0.2f);

		//float AnglePercent = 1.0f - (DotProduct / .94f);
		//int32 SpeedMPH = UKismetMathLibrary::Round(GetVelocity().Size() / 20.0f);
		
		float Dir = FMath::Abs(FVector::DotProduct(GetActorForwardVector(), GetVelocity().GetSafeNormal()));
		
		if (Dir > StraightenOutANGLEValue  && bUsingHandBrake == false && FrictionForce == HandBrakeFriction && IsTurning == false)
		{
			//UE_LOG(LogClass, Log, TEXT("Check 1"));
			if (FMath::Abs(Collider->GetPhysicsAngularVelocity().Z) < StraightenOutTURNValue)
			{
				//UE_LOG(LogClass, Log, TEXT("Check 2"));

				FrictionForce = DriveFriction;
				//UE_LOG(LogClass, Log, TEXT("Should Straighten. DotProduct: %f , AngularVelocity: %f"), Dir, Collider->GetPhysicsAngularVelocity().Z);
				/*
				if (!FMath::IsNearlyEqual(FrictionForce, DriveFriction, 2.0f))
				{
					UE_LOG(LogClass, Log, TEXT("Should Straighten. DotProduct: %f , AngularVelocity: %f"), Dir, Collider->GetPhysicsAngularVelocity().Z);
					FrictionForce = FMath::Lerp(FrictionForce, DriveFriction, DeltaTime);
				}
				*/
			}
		}
		if (Collider->IsSimulatingPhysics())
		{
			
			Collider->AddForce(GetActorRightVector() * DotProduct);
			if (FrictionForce != HandBrakeFriction)
			{
				
				Collider->AddTorque(FVector(0, 0, (CurrentSpeed / 2) * TurnForce * CurrentSpeedSteerAngle));
			}
			else
			{
				
				Collider->AddTorque(FVector(0, 0, (CurrentSpeed / 2) * TurnForce * CurrentSpeedDriftSteerAngle));
				if (LastKnownSteerAngle != NULL)
				{
					Collider->AddTorque(FVector(0, 0, (CurrentSpeed / 2) * TurnForce * LastKnownSteerAngle));
				}
			}
		}
		float RightDotProduct = FMath::Abs(FVector::DotProduct(GetActorRightVector(), GetVelocity().GetSafeNormal()));
		//UE_LOG(LogClass, Log, TEXT("Angle:  %f"), DotProduct);
		float AngleFactor = RightDotProduct / 1.0f;
		if (FrictionForce == HandBrakeFriction)
		{

			if (RightDotProduct > 0.3f)
			{
				bIsDrifting = true;
				
				
				
				CurrentDriftBrakeStrength = FMath::Lerp(LowDriftBrakeStrength, HighDriftBrakeStrength, AngleFactor);
				CurrentDriftAccelStrength = FMath::Lerp(LowDriftAccelStrength, HighDriftAccelStrength, AngleFactor);
				CurrentDriftCounterSteerStrength = FMath::Lerp(LowDriftCounterSteerStrength, HighDriftCounterSteerStrength, AngleFactor);
				Collider->AddForce(-GetVelocity().GetSafeNormal() * Collider->GetMass() * CurrentDriftBrakeStrength);
				UE_LOG(LogClass, Log, TEXT("AccelStrength:  %f"), CurrentDriftAccelStrength);
			}
			else
			{
				bIsDrifting = false;
				LastKnownSteerAngle = NULL;
				CurrentDriftAccelStrength = FMath::Lerp(CurrentDriftAccelStrength, 1.0f, AngleFactor);
			}
		}
		else
		{
			CurrentDriftAccelStrength = FMath::Lerp(CurrentDriftAccelStrength, 1.0f, AngleFactor);
			bIsDrifting = false;
		}

		
		if (IsAccelerating == false)
		{
			if (Collider->IsSimulatingPhysics())
			{
				Collider->AddForce(-GetVelocity() * Collider->GetMass() * RollingBreakStrength);
			}
		}
		
	}
	else
	{
		bIsDrifting = false;
	}
}

void ACar::Decelerate(float Value)
{

		
	FVector SurfaceDirection = UKismetMathLibrary::ProjectVectorOnToPlane(GetActorRotation().UnrotateVector(GetVelocity()), FL_Hit.ImpactNormal).GetSafeNormal();
	Collider->AddForce(GetVelocity() * Collider->GetMass() * BreakStrength * Value * FrictionForce);
	//Collider->AddImpulseAtLocation(SurfaceDirection * DecelForce * Value, GetActorLocation());



}
void ACar::Accelerate(float Value)
{

	if (Value != 0.0f)
	{
		IsAccelerating = true;
		FVector SurfaceDirection = UKismetMathLibrary::ProjectVectorOnToPlane(GetActorForwardVector(), FL_Hit.ImpactNormal).GetSafeNormal();
		if (CurrentSpeed < MaxSpeed)
		{
			if (bIsDrifting)
			{


				Collider->AddImpulseAtLocation(SurfaceDirection * AccelForce * Value * CurrentDriftAccelStrength, GetActorLocation());
			}
			else
			{
				Collider->AddImpulseAtLocation(SurfaceDirection * AccelForce * Value, GetActorLocation());
			}
				
		}
		else
		{
			//UE_LOG(LogClass, Log, TEXT("MaxSpeed"));
		}
	}
	else
	{
		IsAccelerating = false;
	}
		

		

}
void ACar::Turn(float Value)
{
	TurnAxisValue = Value;

	SpeedFactor = (GetVelocity().Size() / SpeedDivisionScale) / MaxSpeed;
	CurrentSpeedSteerAngle = FMath::Lerp(LowSpeedSteerAngle, HighSpeedSteerAngle, SpeedFactor);
	CurrentSpeedSteerAngle *= Value;
	CurrentSpeedDriftSteerAngle = FMath::Lerp(LowSpeedDriftSteerAngle, HighSpeedDriftSteerAngle, SpeedFactor);
	CurrentSpeedDriftSteerAngle *= Value;
	if (FrictionForce == HandBrakeFriction && Value != 0.0f)
	{
		LastKnownSteerAngle = CurrentSpeedDriftSteerAngle * CurrentDriftCounterSteerStrength;
	}
	//float StraightenForce = 1.0f * FrictionForce * FVector::DotProduct(GetActorRotation().UnrotateVector(GetVelocity()), Collider->GetPhysicsAngularVelocity());
	if (IsGrounded)
	{
		
		if (Value != 0.0f)
		{
			IsTurning = true;
			if (bUsingHandBrake)
			{
				TurnForce = DRIFTSteerForce;
			}
			else
			{
				TurnForce = BASESteerForce;
			}

		}
		else
		{
			if (FrictionForce != HandBrakeFriction) {
				Collider->AddTorque(FVector(0, 0, -Collider->GetPhysicsAngularVelocity().Z  * (CurrentSpeed / 2) * TurnForce));
			}
			//Collider->AddForce(GetActorRightVector() * StraightenForce);
			IsTurning = false;
			//Collider->SetAngularDamping(BASEAngularDamping);
		}
	}
	
}

void ACar::ApplyHandBrake()
{
	FrictionForce = HandBrakeFriction;
	bUsingHandBrake = true;
}
void ACar::ReleaseHandBrake()
{
	bUsingHandBrake = false;
	
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Throttle", this, &ACar::Accelerate);
	PlayerInputComponent->BindAxis("Brake", this, &ACar::Decelerate);
	PlayerInputComponent->BindAxis("Steer", this, &ACar::Turn);
	PlayerInputComponent->BindAction("HandBrake",IE_Pressed, this, &ACar::ApplyHandBrake);
	PlayerInputComponent->BindAction("HandBrake", IE_Released, this, &ACar::ReleaseHandBrake);
}


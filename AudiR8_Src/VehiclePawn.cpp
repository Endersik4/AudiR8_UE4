// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Components/BoxComponent.h"
#include "MyFirstPersonCharacter.h"
#include "Kismet/GameplayStatics.h"

static const FName NAME_SteerInput("Steer");
static const FName NAME_ThrottleInput("Thorttle");

AVehiclePawn::AVehiclePawn()
{
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	//Adjust Tire Setting
	Vehicle4W->MinNormalizedTireLoad = 0.f;
	Vehicle4W->MinNormalizedTireLoadFiltered = 0.2f;
	Vehicle4W->MaxNormalizedTireLoad = 2.f;
	Vehicle4W->MaxNormalizedTireLoadFiltered = 2.0f;

	//Torgue Setup
	Vehicle4W->MaxEngineRPM = 15000.f;
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.f, 400.f);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1890.f, 500.f);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(5730.f, 400.f);

	//ADjust the steering
	Vehicle4W->SteeringCurve.GetRichCurve()->Reset();
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(0.f, 1.f);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(40.f, 0.7f);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(120.f, 0.6f);

	Vehicle4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	Vehicle4W->DifferentialSetup.FrontRearSplit = 0.65;

	//Automatic GearBox
	Vehicle4W->TransmissionSetup.bUseGearAutoBox = true;
	Vehicle4W->TransmissionSetup.GearSwitchTime = 0.15f;
	Vehicle4W->TransmissionSetup.GearAutoBoxLatency = 1.0f;

	//Create Spring Arm for our chase camear
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.f;
	SpringArm->bUsePawnControlRotation = true;

	//Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->FieldOfView = 90.f;

	Boks = CreateDefaultSubobject<UBoxComponent>(TEXT("Boks"));

}

void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInAirControl(DeltaTime);
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(NAME_ThrottleInput, this, &AVehiclePawn::ApplyThorttle);
	PlayerInputComponent->BindAxis(NAME_SteerInput, this, &AVehiclePawn::ApplySteering);
	PlayerInputComponent->BindAxis("LookUp", this, &AVehiclePawn::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AVehiclePawn::Turn);

	PlayerInputComponent->BindAction("HandBrake", IE_Pressed, this, &AVehiclePawn::OnHandBrakePressed);
	PlayerInputComponent->BindAction("HandBrake", IE_Released, this, &AVehiclePawn::OnHandBrakeReleased);

	InputComponent->BindAction("GetIn", IE_Pressed, this, &AVehiclePawn::GetOut);
}

void AVehiclePawn::ApplyThorttle(float Val)
{
	if (CzyInput == false)
	{
		GetVehicleMovementComponent()->SetThrottleInput(Val);
	}
}
void AVehiclePawn::ApplySteering(float Val)
{
	if (CzyInput == false)
	{
		GetVehicleMovementComponent()->SetSteeringInput(Val);
	}
}
void AVehiclePawn::LookUp(float Val)
{
	if (Val != 0.f)
	{
		AddControllerPitchInput(Val);
	}
}
void AVehiclePawn::Turn(float Val)
{
	if (Val != 0.f)
	{
		AddControllerYawInput(Val);
	}
}
void AVehiclePawn::OnHandBrakePressed()
{
	if (CzyInput == false)
	{
		GetVehicleMovementComponent()->SetHandbrakeInput(true);
	}
}
void AVehiclePawn::OnHandBrakeReleased()
{
	if (CzyInput == false)
	{
		GetVehicleMovementComponent()->SetHandbrakeInput(false);
	}
}
void AVehiclePawn::UpdateInAirControl(float DeltaTime)
{
	if (CzyInput == false)
	{
		if (UWheeledVehicleMovementComponent4W* Vehicle4W = Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
		{
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			const FVector TraceStart = GetActorLocation() + FVector(0.f, 0.f, 50.f);
			const FVector TraceEnd = GetActorLocation() - FVector(0.f, 0.f, 200.f);

			FHitResult Hit;

			//Check if car is flipped on its side
			const bool bInAir = !GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
			const bool bNotGrounded = FVector::DotProduct(GetActorUpVector(), FVector::UpVector) < 0.1f;

			//Only Allow in Air_Movemnt 
			if (bInAir || bNotGrounded)
			{
				const float ForwardInput = InputComponent->GetAxisValue(NAME_ThrottleInput);
				const float RightInput = InputComponent->GetAxisValue(NAME_SteerInput);

				//in car is grounded allow p[layer to roll car over
				const float AirMovementForcePitch = 3.f;
				const float AirMovementForceRoll = !bInAir && bNotGrounded ? 20.f : 3.f;

				if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
				{
					const FVector MovementVector = FVector(RightInput * -AirMovementForceRoll, ForwardInput * AirMovementForcePitch, 0.f) * DeltaTime * 200.f;
					const FVector NewAngularMovement = GetActorRotation().RotateVector(MovementVector);

					VehicleMesh->SetPhysicsAngularVelocity(NewAngularMovement, true);
				}
			}

		}
	}
}

void AVehiclePawn::OdpalHamulce()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AVehiclePawn::WylaczHamulce()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AVehiclePawn::GetOut()
{
	if (CzyInput == false)
	{
		APlayerController* controller;
		controller = UGameplayStatics::GetPlayerController(this, 0);
		controller->UnPossess();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector LocCar = GetVehicleMovementComponent()->GetActorLocation();
		FRotator RotCar = GetActorRotation();
		if ((RotCar.Yaw >= -20.f && RotCar.Yaw <= 20.f) || (RotCar.Yaw >= -160.f && RotCar.Yaw >= 160.f)) LocCar.Y += 250.f;
		else LocCar.X += 250.f;
		LocCar.Z += 150.f;
		auto NewPawn = GetWorld()->SpawnActor<AMyFirstPersonCharacter>(Character, FTransform(LocCar), SpawnParameters);
		NewPawn->Koniec = true;
		controller->Possess(NewPawn);
	}
}



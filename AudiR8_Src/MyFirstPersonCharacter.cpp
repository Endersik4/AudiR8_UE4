// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstPersonCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "VehiclePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Obrot.h"


// Sets default values
AMyFirstPersonCharacter::AMyFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->AttachTo(RootComponent);
	Cam->SetRelativeLocation(FVector(0.f, 0.f, 40.f));

	OnActorBeginOverlap.AddDynamic(this, &AMyFirstPersonCharacter::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyFirstPersonCharacter::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AMyFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Hori", this, &AMyFirstPersonCharacter::HoriMove);
	InputComponent->BindAxis("Vert", this, &AMyFirstPersonCharacter::VertMove);

	InputComponent->BindAxis("HoriRot", this, &AMyFirstPersonCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AMyFirstPersonCharacter::VertRot);

	InputComponent->BindAction("GetIn", IE_Pressed, this, &AMyFirstPersonCharacter::GetIn);
	InputComponent->BindAction("Button", IE_Pressed, this, &AMyFirstPersonCharacter::CzyPrzycisk);

}

void AMyFirstPersonCharacter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Car")) CzyGetIn = true;

	if (OtherActor->ActorHasTag("Audi")) JakiSamochod = 1;
	else if (OtherActor->ActorHasTag("Sport")) JakiSamochod = 2;
	else if (OtherActor->ActorHasTag("Truck")) JakiSamochod = 3;
	else if (OtherActor->ActorHasTag("SUV")) JakiSamochod = 4;
	else if (OtherActor->ActorHasTag("Pickup")) JakiSamochod = 5;
	else if (OtherActor->ActorHasTag("Hatchback")) JakiSamochod = 6;

	UE_LOG(LogTemp, Warning, TEXT("cos %i"), JakiSamochod);
}

void AMyFirstPersonCharacter::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	CzyGetIn = false;
}

void AMyFirstPersonCharacter::CzyPrzycisk()
{
	if (Bool_Przycisk == true)
	{
		Mozna_Przycisk = true;
	}
}

void AMyFirstPersonCharacter::HoriMove(float Val)
{
	if (Val)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AMyFirstPersonCharacter::VertMove(float Val)
{
	if (Val)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AMyFirstPersonCharacter::HoriRot(float Val)
{
	if (Val)
	{
		AddActorLocalRotation(FRotator(0, Val, 0));
	}
}

void AMyFirstPersonCharacter::VertRot(float Val)
{
	if (Val)
	{
		float Temp = Cam->GetRelativeRotation().Pitch + Val;

		if (Temp < 80 && Temp > -80)
		{
			Cam->AddLocalRotation(FRotator(Val, 0, 0));
		}

	}
}

void AMyFirstPersonCharacter::GetIn()
{
	if (CzyGetIn == true)
	{
		if (Koniec == false)
		{
			TArray<AActor*> ObrotActor;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObrot::StaticClass(), ObrotActor);

			for (int i = 0; i != ObrotActor.Num(); i++)
			{
				auto ObrotCast = Cast<AObrot>(ObrotActor[i]);
				if (ObrotCast->CzyKorzystac == true)
				{
					ObrotCast->CzyMozna = true;
					break;
				}
			}
		}
		TArray<AActor*> Vehicle;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehiclePawn::StaticClass(), Vehicle);
		APlayerController* controller;
		controller = UGameplayStatics::GetPlayerController(this, 0);
		controller->UnPossess();

		for (int i = 0; i != Vehicle.Num(); i++)
		{
			auto HoldFPPawn = Cast<AVehiclePawn>(Vehicle[i]);

			if (HoldFPPawn->JakieAuto == JakiSamochod)
			{
				controller->Possess(HoldFPPawn);
				if (Koniec == false)
				{
					HoldFPPawn->OdpalHamulce();
					HoldFPPawn->CzyInput = true;
				}
			}
		}
		
		Koniec = true;
		CzyGetIn = false;
		Destroy();
	}
	
}


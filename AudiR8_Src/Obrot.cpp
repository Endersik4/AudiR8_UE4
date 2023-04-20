// Fill out your copyright notice in the Description page of Project Settings.


#include "Obrot.h"
#include "Brama.h"
#include "Kismet/GameplayStatics.h"
#include "VehiclePawn.h"

// Sets default values
AObrot::AObrot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Obrot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obrot"));
	RootComponent = Obrot;

}

// Called when the game starts or when spawned
void AObrot::BeginPlay()
{
	Super::BeginPlay();
	
	KoncowaRotacja = GetActorRotation();
	Rotacja_Z = KoncowaRotacja.Yaw;
	Rotacja_Z += 175.f;
	//KoncowaRotacja.Yaw += 180.f;
}

// Called every frame
void AObrot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CzyMozna == true && CzyKorzystac == true)
	{
		//SetActorRotation(FMath::RInterpTo(GetActorRotation(), KoncowaRotacja, DeltaTime, 0.3f));
		KoncowaRotacja.Yaw += 0.4f;
		SetActorRotation(KoncowaRotacja);
		if (KoncowaRotacja.Yaw >= 269.9f) CzyMozna = false;
	}

	if (CzyJuz == false && KoncowaRotacja.Yaw >= 269.9f && CzyKorzystac == true)
	{
		TArray<AActor*> BramaActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrama::StaticClass(), BramaActor);
		
		for (int i = 0; i != BramaActor.Num(); i++)
		{
			auto BramaCast = Cast<ABrama>(BramaActor[i]);
			if (BramaCast->CzyKorzystac == true)
			{
				BramaCast->Mozna = true;
				break;
			}
		}
		
		TArray<AActor*> Vehicle;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehiclePawn::StaticClass(), Vehicle);

		for (int i = 0; i != Vehicle.Num(); i++)
		{
			auto HoldFPPawn = Cast<AVehiclePawn>(Vehicle[i]);

			if (HoldFPPawn->JakieAuto == 1)
			{
				HoldFPPawn->WylaczHamulce();
				HoldFPPawn->CzyInput = false;
			}
		}

		CzyJuz = true;
	}

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Przycisk.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MyFirstPersonCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"

// Sets default values
APrzycisk::APrzycisk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Przycisk_SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Przycisk"));

	Kolizja = CreateDefaultSubobject<UBoxComponent>(TEXT("Kolizja"));
	Kolizja->SetGenerateOverlapEvents(true);
	Kolizja->OnComponentBeginOverlap.AddDynamic(this, &APrzycisk::Kolizja_OnOverlapBegin);
	Kolizja->OnComponentEndOverlap.AddDynamic(this, &APrzycisk::Kolizja_OnOverlapEnd);

}

// Called when the game starts or when spawned
void APrzycisk::BeginPlay()
{
	Super::BeginPlay();
	Location = Przycisk_SM->GetRelativeLocation();
	Location.X += 40.f;
}

// Called every frame
void APrzycisk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CzyTick == true && CzyClick == false)
	{
		TArray<AActor*> Pawn;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyFirstPersonCharacter::StaticClass(), Pawn);
		auto PawnCast = Cast<AMyFirstPersonCharacter>(Pawn[0]);

		if (PawnCast->Mozna_Przycisk == true)
		{
			Przycisk_SM->SetRelativeLocation(FMath::VInterpTo(Przycisk_SM->GetRelativeLocation(), Location, DeltaTime, 3.1f));
			if (Przycisk_SM->GetRelativeLocation().X >= Location.X - 0.2)
			{
				CzyClick = true;
				PawnCast->Mozna_Przycisk = false;
			}
			ZmianaKoloru();
		}
	}

}

void APrzycisk::Kolizja_OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Gracz"))
	{
		auto Pawn = Cast<AMyFirstPersonCharacter>(OtherActor);
		Pawn->Bool_Przycisk = true;
		CzyTick = true;
	}
}

void APrzycisk::Kolizja_OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Gracz"))
	{
		auto Pawn = Cast<AMyFirstPersonCharacter>(OtherActor);
		Pawn->Bool_Przycisk = false;
		CzyTick = false;
	}
}

void APrzycisk::ZmianaKoloru()
{
	TArray<AActor*> Door;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoor::StaticClass(), Door);
	for (int i = 0; i != Door.Num(); i++)
	{
		if (Door[i]->ActorHasTag("Te"))
		{
			auto DoorCast = Cast<ADoor>(Door[i]);
			DoorCast->CzyZmianaKoloru = true;
		}
	}
	
}
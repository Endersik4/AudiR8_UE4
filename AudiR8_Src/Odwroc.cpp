// Fill out your copyright notice in the Description page of Project Settings.


#include "Odwroc.h"
#include "Components/TextRenderComponent.h"
#include "MyFirstPersonCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOdwroc::AOdwroc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Points"));
	Text->SetText(FText::FromString("Odwroc sie :)"));
}

// Called when the game starts or when spawned
void AOdwroc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOdwroc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Hide == false)
	{
		TArray<AActor*> Pawn;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyFirstPersonCharacter::StaticClass(), Pawn);
		auto PawnCast = Cast<AMyFirstPersonCharacter>(Pawn[0]);
		FRotator Rotacja;
		Rotacja = PawnCast->GetActorRotation();
		if (Rotacja.Yaw >= 90.f || Rotacja.Yaw <= -90.f)
		{
			SetActorHiddenInGame(true);
			Hide = true;
		}
	}
}


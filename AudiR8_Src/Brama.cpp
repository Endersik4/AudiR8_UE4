// Fill out your copyright notice in the Description page of Project Settings.


#include "Brama.h"

// Sets default values
ABrama::ABrama()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Brama = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brama"));
	RootComponent = Brama;

}

// Called when the game starts or when spawned
void ABrama::BeginPlay()
{
	Super::BeginPlay();
	
	KoncowaRotacja = GetActorRotation();
	KoncowaRotacja.Roll -= 120.f;
}

// Called every frame
void ABrama::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Mozna == true && CzyKorzystac == true)
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), KoncowaRotacja, DeltaTime, 0.2f));
	}

}


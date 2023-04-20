// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brama.generated.h"

UCLASS()
class MYPROJECT_API ABrama : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrama();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool Mozna;
	UPROPERTY(EditAnywhere)
		bool CzyKorzystac;

private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Brama;
	FRotator KoncowaRotacja;
	

};

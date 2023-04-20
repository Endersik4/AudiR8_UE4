// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obrot.generated.h"

UCLASS()
class MYPROJECT_API AObrot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObrot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CzyMozna;
	UPROPERTY(EditAnywhere)
		bool CzyKorzystac;
private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Obrot;
	FRotator KoncowaRotacja;

	float Rotacja_Z;
	bool CzyJuz;
};

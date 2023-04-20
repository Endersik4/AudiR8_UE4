// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Odwroc.generated.h"

UCLASS()
class MYPROJECT_API AOdwroc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOdwroc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool Hide;
	UPROPERTY(EditAnywhere)
		class UTextRenderComponent* Text;

};

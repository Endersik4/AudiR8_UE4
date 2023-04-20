// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Przycisk.generated.h"

UCLASS()
class MYPROJECT_API APrzycisk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrzycisk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Przycisk_SM;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Kolizja;

	UFUNCTION()
		void Kolizja_OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Hit);

	UFUNCTION()
		void Kolizja_OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool CzyTick;
	bool CzyClick;
	FVector Location;
	void ZmianaKoloru();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

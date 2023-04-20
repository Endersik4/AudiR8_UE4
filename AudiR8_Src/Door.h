// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class MYPROJECT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Box_OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Hit);

	bool CzyZmianaKoloru;
	void ZmianaKoloruAudi();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Koniec;

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	bool CzyOpen;
	FRotator KoncowaRotacja;
	bool IleJuz;
	int NumerAudi;
	TArray<AActor*> Audi;
	int Jakikolor;
	FTimerHandle Timer_1;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_1;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_2;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_3;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_4;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_5;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_6;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_7;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_8;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_9;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_10;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_Reszta_1;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_Reszta_2;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_Reszta_3;
};

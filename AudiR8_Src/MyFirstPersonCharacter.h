// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyFirstPersonCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	bool Koniec;
	int JakiSamochod; // 1 - Audi, 2 - Sportowy, 3 - Truck, 4 - SUV, 5 - Pickup, 6 - Hatchback

	void CzyPrzycisk();
	bool Bool_Przycisk;
	bool Mozna_Przycisk;

private:
	void HoriMove(float Val);
	void VertMove(float Val);

	void HoriRot(float Val);
	void VertRot(float Val);

	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* Cam;

	void GetIn();
	bool CzyGetIn;



};

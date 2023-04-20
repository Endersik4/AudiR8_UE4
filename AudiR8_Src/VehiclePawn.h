// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehiclePawn.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT_API AVehiclePawn : public AWheeledVehicle
{
	GENERATED_BODY()

public:

	AVehiclePawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//Thorttle Steering
	void ApplyThorttle(float Val);
	void ApplySteering(float Val);

	//Look Around
	void LookUp(float Val);
	void Turn(float Val);

	//HandBrak
	void OnHandBrakePressed();
	void OnHandBrakeReleased();

	//Update in Air
	void UpdateInAirControl(float DeltaTime);

	UPROPERTY(EditAnywhere)
		int JakieAuto; // 1 - Audi, 2 - Sportowy, 3 - Truck, 4 - SUV, 5 - Pickup, 6 - Hatchback

	void OdpalHamulce();
	void WylaczHamulce();
	bool CzyInput;

protected:

	//Spring arm - poprawna odleglosc miedzy kamera a samochodem
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	//Camera COmponent ktora bedzie nasza kamera
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Boks;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyFirstPersonCharacter> Character;

	void GetOut();
	bool CzyGetOut;

};

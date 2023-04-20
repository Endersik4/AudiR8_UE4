// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VehiclePawn.h"
#include "Odwroc.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetGenerateOverlapEvents(true);
	Box->SetupAttachment(Mesh);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADoor::Box_OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehiclePawn::StaticClass(), Audi);
	for (int i = 0; i != Audi.Num(); i++)
	{
		auto AudiCastBegin = Cast<AVehiclePawn>(Audi[i]);
		if (AudiCastBegin->JakieAuto == 1)
		{
			NumerAudi = i;
			break;
		}
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CzyOpen == true)
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), KoncowaRotacja, DeltaTime, 3.1f));
	}

}

void ADoor::Box_OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (IleJuz == false)
	{
		if (CzyZmianaKoloru == true)
		{
			GetWorldTimerManager().SetTimer(Timer_1, this, &ADoor::ZmianaKoloruAudi, 5.f, true, 8.f);
		}
		KoncowaRotacja = GetActorRotation();
		KoncowaRotacja.Yaw -= 90.f;
		CzyOpen = true;
		IleJuz = true;

		TArray<AActor*> Odw;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOdwroc::StaticClass(), Odw);
		auto OdwCast = Cast<AOdwroc>(Odw[0]);
		OdwCast->Hide = true;
	}
}

void ADoor::ZmianaKoloruAudi()
{
	if (Koniec == false)
	{
		auto AudiCast = Cast<AVehiclePawn>(Audi[NumerAudi]);
		switch (Jakikolor)
		{
		case 0: AudiCast->GetMesh()->SetMaterial(6, Material_1); break;
		case 1: AudiCast->GetMesh()->SetMaterial(6, Material_2); break;
		case 2: AudiCast->GetMesh()->SetMaterial(6, Material_3); break;
		case 3: AudiCast->GetMesh()->SetMaterial(6, Material_4); break;
		case 4: AudiCast->GetMesh()->SetMaterial(6, Material_5); break;
		case 5: AudiCast->GetMesh()->SetMaterial(6, Material_6); break;
		case 6: AudiCast->GetMesh()->SetMaterial(6, Material_7); break;
		case 7: AudiCast->GetMesh()->SetMaterial(6, Material_8); break;
		case 8: AudiCast->GetMesh()->SetMaterial(6, Material_9); break;
		case 9: AudiCast->GetMesh()->SetMaterial(6, Material_10); break;
		}
		if (Jakikolor == 0 || Jakikolor == 4) AudiCast->GetMesh()->SetMaterial(9, Material_Reszta_1);
		else if (Jakikolor == 2) AudiCast->GetMesh()->SetMaterial(9, Material_Reszta_3);
		else AudiCast->GetMesh()->SetMaterial(9, Material_Reszta_2);

		Jakikolor++;
		if (Jakikolor >= 10) Jakikolor = 0;
	}
	else GetWorldTimerManager().ClearTimer(Timer_1);
}


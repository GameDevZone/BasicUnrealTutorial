// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	// rotate
	Owner->SetActorRotation(FRotator(0.f, -OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	// rotate
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float TimeElapsed = GetWorld()->GetTimeSeconds();

	// ...
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = TimeElapsed;
	}
	
	if (TimeElapsed - LastDoorOpenTime >= DoorCloseDelay)
	{
		CloseDoor();
	}	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;

	// find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// iterate through to get mass
	for (const auto* Actor:OverlappingActors)
	{
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s on presure plate"), *Actor->GetName());
	}

	return totalMass;
}

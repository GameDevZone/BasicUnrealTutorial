// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	// ray cast reach distance
	UPROPERTY(VisibleAnywhere)
	float Reach = 100.f;
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// called when grab pressed
	void Grab();

	// called when grab release
	void Release();

	// Look for attached physics handle
	void FindPhsicsHandComponent();	
	
	// find and setup input component
	void SetupInputComponent();

	// return hit for first physics body
	const FHitResult GetFirstPhysicsBodyInReach();

	// get line trace start pos
	FVector GetLineTraceStartVector();

	// get line trace end position
	FVector GetLineTraceEndVector();
};

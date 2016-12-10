// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    
    float Reach = 100.f;
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
    
    //Ray-Cast and grabs whats in reach
    void Grab();
    void Release();
    
    //find attached Physics Component
    void FindPhysicsHandleComponent();
    
    //setup input component
    void SetupInputComponent();
    
    //return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
    
    //REFACTORING
    
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    FVector LineTraceEnd;
    
    void GetInfo(OUT FVector* VL, OUT FRotator* RL, OUT FVector* LT);
    
};

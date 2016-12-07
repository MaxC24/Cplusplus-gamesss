// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for Duty!!!!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get Player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotator;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                 OUT PlayerViewPointLocation,
                 OUT PlayerViewPointRotator
    );
    
    // Ray -cast out to reach distance
    UE_LOG(LogTemp, Warning, TEXT("this is the location %s and this is the rotation %s"),
           *PlayerViewPointLocation.ToString(),
           *PlayerViewPointRotator.ToString()
    );
    // see what we hit
}


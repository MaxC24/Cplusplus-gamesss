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
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                 OUT PlayerViewPointLocation,
                 OUT PlayerViewPointRotation
    );
    
    //logout the location coordinates of the pawn:
    
    UE_LOG(LogTemp, Warning, TEXT("Location: %s and Rotation: %s"),
           *PlayerViewPointLocation.ToString(),
           *PlayerViewPointRotation.ToString()
    );
    
//    FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.f, 0.f, 100.f);
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Reach);
    
    //Draw a red trace in the world to visualize
    
    DrawDebugLine(GetWorld(),
                  PlayerViewPointLocation,
                  LineTraceEnd,
                  FColor(255, 0, 0),
                  false,
                  0.f,
                  0.f,
                  10.f
    );
    
    // Ray -cast out to reach distance
    
    // see what we hit
}

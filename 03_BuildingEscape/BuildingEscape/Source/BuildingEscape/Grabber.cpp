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
    
    //Look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(PhysicsHandle){
        
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics Handle Component"), *GetOwner()->GetName());
    }
    
    //Log input Component
    
    if(InputComponent) {
        //BInd Action axis
        
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        
        UE_LOG(LogTemp, Warning, TEXT("I found %s has an input component"), *GetOwner()->GetName());
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab(){
    UE_LOG(TempLog, Warning, TEXT("Grab Pressed"));
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
    
    
    UE_LOG(LogTemp, Warning, TEXT("Location: %s and Rotation: %s"),
           *PlayerViewPointLocation.ToString(),
           *PlayerViewPointRotation.ToString()
    );
    
 
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
    
    //Setup query params
    
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
//
    // Line-Trace Ray-cast out to reach distance
    FHitResult Hit;
    
    GetWorld()->LineTraceSingleByObjectType(OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );

    AActor* ActorHit = Hit.GetActor();
    
    // see what we hit
    if(ActorHit){
        UE_LOG(LogTemp, Warning, TEXT("Am hitting %s"), *ActorHit->GetName());
    }

    
}


















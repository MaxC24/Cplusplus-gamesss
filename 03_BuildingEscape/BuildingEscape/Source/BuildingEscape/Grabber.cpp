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
    
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
    
}


void UGrabber::FindPhysicsHandleComponent(){
    
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    
    if(!PhysicsHandle){ UE_LOG(LogTemp, Error, TEXT("%s missing physics Handle Component"), *GetOwner()->GetName()); }
}

void UGrabber::SetupInputComponent(){
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    
    //Log input Component
    
    if(InputComponent) {
        //BInd Action axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
        UE_LOG(LogTemp, Warning, TEXT("I found %s has an input component"), *GetOwner()->GetName());
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
    }

}

void UGrabber::Grab(){
    UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
    
    //Linetrace and find any object with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    //If we hit something then attach a physics handle
    
    if(ActorHit){
        PhysicsHandle->GrabComponentAtLocationWithRotation(
            ComponentToGrab,
            NAME_None,
            ComponentToGrab->GetOwner()->GetActorLocation(),
            ComponentToGrab->GetOwner()->GetActorRotation()
        );
    }
}

void UGrabber::Release() {
    //release Physics
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    // Get Player view point this tick
    GetInfo(&PlayerViewPointLocation, &PlayerViewPointRotation, &LineTraceEnd);
    
    if(PhysicsHandle->GrabbedComponent) { PhysicsHandle->SetTargetLocation(LineTraceEnd); }
    
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
    
    GetInfo(&PlayerViewPointLocation, &PlayerViewPointRotation, &LineTraceEnd);
    
    UE_LOG(LogTemp, Warning, TEXT("This is the PlayerViewPointLocation: %s"), *PlayerViewPointLocation.ToString());
    
    //Setup query params
    
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    // Line-Trace Ray-cast out to reach distance
    FHitResult Hit;
    
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    
    AActor* ActorHit = Hit.GetActor();
    
    // see what we hit
    if(ActorHit){ UE_LOG(LogTemp, Warning, TEXT("Am hitting %s"), *ActorHit->GetName()) }
    return Hit;
}

//REFACTORING;

void UGrabber::GetInfo(OUT FVector* VL, OUT FRotator* RL, OUT FVector* LT){
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT *VL, OUT *RL );
    *LT = *VL + (RL->Vector()* Reach);
}















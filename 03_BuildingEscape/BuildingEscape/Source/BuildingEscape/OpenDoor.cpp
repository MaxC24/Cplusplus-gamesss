// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    Owner = GetOwner();
}

void UOpenDoor::OpenDoor() {
    OnOpenRequest.Broadcast();
    //Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
    
}

void UOpenDoor::CloseDoor() {
    
    
    Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    //Poll the Trigger Volume
    if(GetTotalMassOfActorOnPlate() > 50.f){
        //if the ActorThatOpens is in the volume
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay){
        CloseDoor();
    }
    
}

float UOpenDoor::GetTotalMassOfActorOnPlate(){
    float TotalMass = 0.f;
    
    //find all the overlapping actors
    TArray<AActor*> OverlappingActors;
    if(!PressurePlate) return TotalMass;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    
    //iterate through them and calculate their masses
    for(const auto& Actor: OverlappingActors) {
        UE_LOG(LogTemp, Warning, TEXT("My Name is %s: "), *Actor->GetName());
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }

    return TotalMass;
}



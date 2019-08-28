// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor:: OpenDoor()
{
    // Set the door rotation
    Owner -> SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor:: CloseDoor()
{
    // Create a rotator
    Owner -> SetActorRotation(FRotator(0.0f, 60.0f, 0.0f));

}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find owning Actor
    ActorThatOpens = GetWorld() -> GetFirstPlayerController() -> GetPawn();
    
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Poll the Trigger Volume
    // If the ActorThatOpens is in the volume
    if( PressurePlate -> IsOverlappingActor(ActorThatOpens))
    {
        
        OpenDoor();
        float LastTimeDoorOpen = GetWorld() -> GetTimeSeconds();
    }
    
    // Check if time to close the door
    if(GetWorld() -> GetTimeSeconds() - LastTimeDoorOpen > DoorDelay)
    {
        CloseDoor();
    }

}


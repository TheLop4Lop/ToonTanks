// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActorMovement();

	ActorRotation();

}

void UMoverComponent::ActorMovement()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector Destination = OriginalLocation + SetOffLocation;
	FVector NewLocation = FVector::ZeroVector;

	float Speed = (FVector::Distance(OriginalLocation, Destination)/ TimeToMove);

	if(bShouldMove)
	{
		switch (bBackwardsMove)
		{
		case true:
			NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, UGameplayStatics::GetWorldDeltaSeconds(this), Speed);
			GetOwner()->SetActorLocation(NewLocation);

			CheckConditionToBackwards(CurrentLocation, Destination);
			break;
		
		default:
			NewLocation = FMath::VInterpConstantTo(CurrentLocation, Destination, UGameplayStatics::GetWorldDeltaSeconds(this), Speed);
			GetOwner()->SetActorLocation(NewLocation);

			CheckConditionToBackwards(CurrentLocation, Destination);
			break;
		}

	}
	
}

void UMoverComponent::ActorRotation()
{
	GetOwner()->AddActorLocalRotation(Rotation * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void UMoverComponent::CheckConditionToBackwards(FVector& Current, FVector& Destination)
{
	if(Current == OriginalLocation)
	{
		SetBackwardsMovement(false);
	}else if(Current == Destination)
	{
		SetBackwardsMovement(true);
	}

}

void UMoverComponent::SetBackwardsMovement(bool bBackward)
{
	bBackwardsMove = bBackward;
}

void UMoverComponent::SetShouldMove(bool bMove)
{
	bShouldMove = bMove;
}
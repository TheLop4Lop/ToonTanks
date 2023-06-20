// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetPhysicsHandle())
	{
		FVector TargetLocation = (GetComponentLocation() + GrabberModifier) + (GetForwardVector() * (GrabDistance/2));
		GetPhysicsHandle()->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabberComponent::Grab()
{
	if(GetPhysicsHandle())
	{
		FHitResult HitResult;

		if(GrabObjectInReach(HitResult))
		{
			//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5); 

			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			HitComponent->WakeAllRigidBodies();

			GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
				HitComponent, 
				NAME_None, 
				HitResult.ImpactPoint,
				GetComponentRotation()
			);
		}

	}

}

void UGrabberComponent::Release()
{	
	if(GetPhysicsHandle())
	{
		GetPhysicsHandle()->ReleaseComponent();
	}

}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle()
{
	//Checks if the variable is pointing to nullptr, then returns the HandleComponent
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr, check code!"));
	}
	
	return Result;
	
}

bool UGrabberComponent::GrabObjectInReach(FHitResult& HitResult) const
{
	FVector StartVector = GetComponentLocation();
	FVector EndVector = StartVector + (GetForwardVector() * GrabDistance);

	//DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red);
	//DrawDebugSphere(GetWorld(), EndVector, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabSphereRadious);

	return GetWorld()->SweepSingleByChannel(
		HitResult, 
		StartVector, 
		EndVector, 
		FQuat::Identity, 
		ECC_GameTraceChannel1,
		Sphere
	);

}
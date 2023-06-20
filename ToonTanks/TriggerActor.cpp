// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "MoverComponent.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = MeshComponent;

	BoxCollision_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Blue"));
	BoxCollision_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Red"));

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();

	MoverComponent = Cast<UMoverComponent>(ATriggerActor::GetComponentByClass(UMoverComponent::StaticClass()));

}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MoverComponent)
	{
		MoverComponent->SetShouldMove(SetbMove());
	}

}

AActor* ATriggerActor::GetBoxActors(UBoxComponent* Box)
{
	TArray<AActor*> Actors;
	Box->GetOverlappingActors(Actors);

	for(AActor* Actor: Actors)
	{
		if(Actor->ActorHasTag(NameTagToUnlockBlue) || Actor->ActorHasTag(NameTagToUnlockRed))
		{
			return Actor;
		}
	}

	return nullptr;
}

bool ATriggerActor::SetbMove()
{
	if(GetBoxActors(BoxCollision_1) != nullptr && GetBoxActors(BoxCollision_2) != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("true"));
		return true;
	}
	
	UE_LOG(LogTemp, Display, TEXT("false"));
	return false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthToken.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

// Sets default values
AHealthToken::AHealthToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(CapsuleComponent);

}

// Called when the game starts or when spawned
void AHealthToken::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}

// Called every frame
void AHealthToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthToken::SetHealth()
{
		//HealthComponent->SetNewHealth(HealthComponent->GetMaxHealth());
		UHealthComponent* HealthComponent;

		HealthComponent = Cast<UHealthComponent>(Tank->GetComponentByClass(UHealthComponent::StaticClass()));
		HealthComponent->SetNewHealth(HealthComponent->GetMaxHealth());

}

void AHealthToken::OnHit()
{
	if(Tank)
	{
		UE_LOG(LogTemp, Display, TEXT("EEEEEEYYY!"));
		if(DestructionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation(), 0.5f);
		}

		SetHealth();
		Destroy();
	}
	
}

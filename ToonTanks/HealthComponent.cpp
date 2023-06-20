// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTakeIn);
	
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTakeIn(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;

	Health -= Damage;
	
	//Checks if Health is 0 or lower and if ToonTanksGameMode is not null
	if(Health <= 0.f && ToonTanksGameMode)
	{
		if(DamageActor)
		{
			ToonTanksGameMode->ActorDied(DamageActor);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

}

float UHealthComponent::GetHealth()
{
	return Health;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetNewHealth(float NewHealth)
{
	Health = NewHealth;
}
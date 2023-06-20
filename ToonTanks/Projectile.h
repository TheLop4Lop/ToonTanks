// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "True"))
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "True"))
	class UProjectileMovementComponent* ProjectileComponent;
	
	UFUNCTION() //Delegate function: Component that hits, Actor has been hit, component has been hit, vector works for magnitud hit and hitresult data
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalInput, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "True"))
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "True"))
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "True"))
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

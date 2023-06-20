// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthToken.generated.h"

UCLASS()
class TOONTANKS_API AHealthToken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthToken();

	UFUNCTION(BlueprintCallable)
	void OnHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Actor properties", meta = (AllowPrivateAccess = "True"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "Actor properties", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DestructionSound;

	class ATank* Tank;

	void SetHealth();


};

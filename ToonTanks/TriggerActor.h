// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

UCLASS()
class TOONTANKS_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess = "True"))
	class UBoxComponent* BoxCollision_1;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess = "True"))
	UBoxComponent* BoxCollision_2;

	UPROPERTY(EditAnywhere)
	FName NameTagToUnlockBlue;

	UPROPERTY(EditAnywhere)
	FName NameTagToUnlockRed;

	class UMoverComponent* MoverComponent;

	AActor* GetBoxActors(UBoxComponent* Box);

	bool SetbMove();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

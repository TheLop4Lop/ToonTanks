// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn movement", meta = (AllowPrivateAccess = "True"))
	float FireDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Attack", meta = (AllowPrivateAccess = "True"))
	float FireRate;

	class ATank* Tank;

	bool CheckForTank();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "True"))
	void CheckForFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

};

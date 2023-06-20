// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void HandleDestruction();

	APlayerController* GetPlayerController() const;

	bool bTankAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Properties", meta = (AllowPrivateAccess = "True"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Properties", meta = (AllowPrivateAccess = "True"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn movement", meta = (AllowPrivateAccess = "True"))
	float Speed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Pawn movement", meta = (AllowPrivateAccess = "True"))
	float TurnRate = 250;

	APlayerController* PlayerController;

	void Move(float value);

	void Turn(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

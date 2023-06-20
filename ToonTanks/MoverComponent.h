// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

	void SetShouldMove(bool bMove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Movement", meta = (AllowPrivateAccess = "True"))
	FVector SetOffLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Actor Movement", meta = (AllowPrivateAccess = "True"))
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = "Actor Movement", meta = (AllowPrivateAccess = "True"))
	float TimeToMove = 0.f;

	UPROPERTY(EditAnywhere, Category = "Actor Movement", meta = (AllowPrivateAccess = "True"))
	bool bShouldMove = true;

	UPROPERTY(EditAnywhere, Category = "Actor Movement", meta = (AllowPrivateAccess = "True"))
	bool bBackwardsMove = false;

	FVector OriginalLocation = FVector::ZeroVector;

	void ActorMovement();
	void ActorRotation();
	void CheckConditionToBackwards(FVector& Current, FVector& Destination);
	void SetBackwardsMovement(bool bBackward);

};

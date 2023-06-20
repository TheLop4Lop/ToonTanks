// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UPhysicsHandleComponent* GetPhysicsHandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	float GrabDistance;

	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	float GrabSphereRadious;

	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	FVector GrabberModifier = FVector(0, 0, 20);

	bool GrabObjectInReach(FHitResult& HitResult) const;
		
};

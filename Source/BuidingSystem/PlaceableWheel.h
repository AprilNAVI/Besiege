// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableBase.h"
#include "PlaceableWheel.generated.h"



/**
 * 
 */
UCLASS()
class BUIDINGSYSTEM_API APlaceableWheel : public APlaceableBase
{
	GENERATED_BODY()

	

public:	
	APlaceableWheel();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Onplaced() override;

	UFUNCTION(BlueprintCallable)
	virtual UPrimitiveComponent* GetBlockJointComponent() override;

	UFUNCTION(BlueprintCallable)
	void ReserverRotation(bool IsRightEqualCoreRight);

	UFUNCTION(BlueprintCallable)
	FVector GetWheelAxis();


};

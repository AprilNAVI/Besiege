// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableBase.h"
#include "PlaceableInteraction.generated.h"

/**
 * 
 */
UCLASS()
class BUIDINGSYSTEM_API APlaceableInteraction : public APlaceableBase
{
	GENERATED_BODY()

public:

	APlaceableInteraction();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Onplaced() override;

	UFUNCTION(BlueprintCallable)
	virtual UPrimitiveComponent* GetBlockJointComponent() override;
	
};

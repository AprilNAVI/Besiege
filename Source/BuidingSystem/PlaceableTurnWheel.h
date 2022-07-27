// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableWheel.h"
#include "PlaceableTurnWheel.generated.h"

/**
 * 
 */
UCLASS()
class BUIDINGSYSTEM_API APlaceableTurnWheel : public APlaceableWheel
{
	GENERATED_BODY()

	APlaceableTurnWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	virtual void Onplaced() override;
	
	virtual UPrimitiveComponent* GetBlockJointComponent() override;
	
};

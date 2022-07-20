// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlaceableBlock.generated.h"

UCLASS()
class APlaceableBlock : public APlaceableBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

    UFUNCTION(BlueprintCallable)
	virtual void Onplaced() override;

	
	virtual UPrimitiveComponent* GetBlockJointComponent() override;

};

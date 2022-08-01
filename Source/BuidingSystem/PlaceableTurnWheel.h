// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PlaceableTurnWheel.generated.h"

/**
 * 
 */
UCLASS()
class BUIDINGSYSTEM_API APlaceableTurnWheel : public APlaceableWheel
{
	GENERATED_BODY()
	
public:
	APlaceableTurnWheel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Onplaced() override;
	
	virtual UPrimitiveComponent* GetBlockJointComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* AxisMesh;
	
};

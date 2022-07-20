// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "PlaceableWheel.generated.h"



/**
 * 
 */
UCLASS()
class BUIDINGSYSTEM_API APlaceableWheel : public APlaceableBase
{
	GENERATED_BODY()

	APlaceableWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* SphereCollison;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCapsuleComponent* CapsuleCollison;
	
	UFUNCTION(BlueprintCallable)
	virtual void Onplaced() override;

	UFUNCTION(BlueprintCallable)
	virtual UPrimitiveComponent* GetBlockJointComponent() override;

	UFUNCTION(BlueprintCallable)
	void ReserverRotation(bool IsRightEqualCoreRight);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

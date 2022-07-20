// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlaceableBase.generated.h"

UENUM(BlueprintType)
enum class ECustomAngularConstraintMotion : uint8
{
	/** No constraint against this axis. */
	Free=0		UMETA(DisplayName="Free"),
	/** Limited freedom along this axis. */
	Limited		UMETA(DisplayName="Limited"),
	/** Fully constraint against this axis. */
	Locked		UMETA(DisplayName="Locked"),

	MAX,
};

UCLASS()
class BUIDINGSYSTEM_API APlaceableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableBase();

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* PreviewMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* ShellMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* ShellMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* ParentBlock;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> ChildBlocks;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float BlockDistance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float PresetMass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	
    virtual void Onplaced();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSelected();

	UFUNCTION(BlueprintImplementableEvent)
    void OnCancelSelected();

	virtual UPrimitiveComponent* GetBlockJointComponent();

	virtual FVector GetCollisonWorldLocation();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetCoreForward();

	UFUNCTION(BlueprintCallable)
    virtual FVector GetCoreRight();

	UFUNCTION(BlueprintCallable)
    virtual FVector GetCoreUp();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECustomAngularConstraintMotion Swing1Limit;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECustomAngularConstraintMotion Swing2Limit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECustomAngularConstraintMotion TwistLimit;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Angle1;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Angle2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TwistAngle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};

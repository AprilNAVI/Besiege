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

UENUM(BlueprintType)
enum class ECustomAngularDriveMode:uint8
{
	SLERP=0,
	TwistAndSwing
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
	APlaceableBase* ParentBlock;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<APlaceableBase*> ChildBlocks;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float BlockDistance;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float PresetMass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	ECustomAngularConstraintMotion Swing1Limit;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	ECustomAngularConstraintMotion Swing2Limit;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	ECustomAngularConstraintMotion TwistLimit;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float Angle1;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float Angle2;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float TwistAngle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bIsLinearBreakable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float LinearBreakThreshold;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bIsAngularBreakable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float AngularBreakThreshold;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bIsAngularPlasticity;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float AngularPlasticityThreshold;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bIsLinearPlasticity;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float LinearPlasticityThreshold;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	ECustomAngularDriveMode AngularDriveMode;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	FRotator PosTarget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bOrientationEnableTwistDrive;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bOrientationEnableSwingDrive;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	FVector VelocityTarget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bVelocityEnableTwistDrive;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	bool bVelocityEnableSwingDrive;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float PositionStrength;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float VelocityStrength;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Joint")
	float MaxForce;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TheWholeMass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int TheComponentNum;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ComponentLevel;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	
    virtual void Onplaced();

	UFUNCTION(BlueprintCallable)
	void OnSelected();

	UFUNCTION(BlueprintCallable)
    void OnCancelSelected();

	virtual UPrimitiveComponent* GetBlockJointComponent();

	virtual FVector GetCollisonWorldLocation();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetCoreForward();

	UFUNCTION(BlueprintCallable)
    virtual FVector GetCoreRight();

	UFUNCTION(BlueprintCallable)
    virtual FVector GetCoreUp();

	UFUNCTION(BlueprintCallable)
	virtual FRotator GetCoreRotation();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetCoreLocation();

	UFUNCTION(BlueprintCallable)
	virtual float GetWholeMass();

	UFUNCTION(BlueprintCallable)
	virtual int GetComponentNums();

	UFUNCTION(BlueprintCallable)
	virtual void AddWholeMass(float Mass);

	UFUNCTION(BlueprintCallable)
	virtual void AddComponentNums();

	UFUNCTION(BlueprintCallable)
	virtual void ReduceComponentNums();

	UFUNCTION(BlueprintImplementableEvent)
	void OnOperate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableBlock.h"
#include "PlaceableWheel.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "JointActor.generated.h"

UCLASS()
class BUIDINGSYSTEM_API AJointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJointActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UPhysicsConstraintComponent* ConstraintComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UArrowComponent* ArrowComponent;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ConstraintActor1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ConstraintActor2;

	UPROPERTY()
	uint32 bDisableCollision_DEPRECATED:1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	virtual void PostLoad() override;
	
	UFUNCTION(BlueprintCallable)
	void ReInitConstaintCompont(UPrimitiveComponent* Component1,UPrimitiveComponent* Component2);

	UFUNCTION(BlueprintCallable)
	void SetLinearBreakable(bool IsLinearBreakable,float LinearBreakThreshold);

	UFUNCTION(BlueprintCallable)
	void SetAngularBreakable(bool IsAngularBreakable,float AngularBreakThreshold);

	UFUNCTION(BlueprintCallable)
	void SetLinearPlasticity(bool IsAngularPlasticity,float LinearPlasticityThreshold);

	UFUNCTION(BlueprintCallable)
	void SetAngularPlasticity(bool IsAngularPlasticity,float AngularPlasticityThreshold);

	UFUNCTION(BlueprintCallable)
	AActor* GetConstraintActor1()
	{
		return  ConstraintActor1;
	}

	UFUNCTION(BlueprintCallable)
	AActor* GetConstraintActor2()
	{
		return  ConstraintActor2;
	}

	UFUNCTION(BlueprintCallable)
	void SetConstraintActor1(AActor* ConstraintActor)
	{
		ConstraintActor1=ConstraintActor;
	}

	UFUNCTION(BlueprintCallable)
	void SetConstraintActor2(AActor* ConstraintActor)
	{
		ConstraintActor2=ConstraintActor;
	}

	UFUNCTION(BlueprintCallable)
	void ConstructStrongConstraint(ECustomAngularConstraintMotion Swing1Limit,float Angle1,ECustomAngularConstraintMotion Swing2Limit,float Angle2,ECustomAngularConstraintMotion TwistLimit,float Twist);

	UFUNCTION(BlueprintCallable)
	void SetAngularDriveMode(ECustomAngularDriveMode DriveMode);

	UFUNCTION(BlueprintCallable)
	void SetAngularOrientationDrive(bool bEnableSwingDrive, bool bEnableTwistDrive);
	
	UFUNCTION(BlueprintCallable)
	void SetAngularVelocityDriveTwistAndSwing(bool bEnableTwistDrive, bool bEnableSwingDrive);

	UFUNCTION(BlueprintCallable)
	void SetAngularOrientationTarget(const FRotator& InPosTarget);

	UFUNCTION(BlueprintCallable)
	void SetAngularVelocityTarget(const FVector& InVelTarget);

	UFUNCTION(BlueprintCallable)
	void SetAngularDriveParams(float PositionStrength, float VelocityStrength, float InForceLimit);
	

};




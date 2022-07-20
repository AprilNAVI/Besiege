// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BesiegePlayerController.h"
#include "JointAcotor.h"
#include "GameFramework/Character.h"
#include "FPS_Character.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class AFPS_Character : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	// Sets default values for this character's properties
	AFPS_Character();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	TSubclassOf<class AActor> DefaultBuildingComponentClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	TSubclassOf<class AActor> CurrentBuildingComponentClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	AActor* CurrenBuildingComponentInstance;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ABesiegePlayerController* BesiegePlayerController;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	APlaceableBase* SelectedBlock;
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsBuilding;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsReset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsHitBlock;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsBlockRotaionReset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	float UpDistance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	FHitResult CrossHairHitResult;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void Fly(float val);

	UFUNCTION(BlueprintCallable)
	void CurrentBlockTurnRight();
	
	UFUNCTION(BlueprintCallable)
    void CurrentBlockTurnLeft();

	FHitResult BuildTrace();

	APlaceableBase* SelectBlock();

	/**
 * Called via input to turn at a given rate.
 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
 */
	void TurnAtRate(float Rate);

	/**
 * Called via input to turn look up/down at a given rate.
 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
 */
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void OnClick();

	UFUNCTION(BlueprintCallable)
	void OnBuilding();

	UFUNCTION(BlueprintCallable)
    void DeleteBlock();

	UFUNCTION(BlueprintCallable)
	AJointAcotor* SpawnConstrainActor(AActor* Parent, AActor* Child);

	AActor* SpawnActorByClass(TSubclassOf<AActor> ActorClass,FTransform Transform);

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BlockAddRotation(float val);

	void ResetBlockRotaion();
	
};

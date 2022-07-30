// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BesiegePlayerController.h"
#include "BlockBuildingComponent.h"
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Buiding)
	UBlockBuildingComponent* BlockBuildingComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ABesiegePlayerController* BesiegePlayerController;


	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void Fly(float val);

	void BlockAddRotation(float val);
	

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
	void OnLeftMouseClick();

	UFUNCTION(BlueprintCallable)
	void OnRightMouseClick();

	UFUNCTION(BlueprintCallable)
    void OnKeyZClick();

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

	UFUNCTION(BlueprintCallable)
	void UnbindMouseInput();

	UFUNCTION(BlueprintCallable)
    void UnbindKeyInput();
	
	
};

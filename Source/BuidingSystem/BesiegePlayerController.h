// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BesiegePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ABesiegePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> HudClass;
	
	virtual void BeginPlay() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BesiegeGameMode.generated.h"

UENUM(BlueprintType)
enum class CurrentGameStateEnum:uint8
{
	Ready,
	Match,
	Placing
};

/**
 * 
 */
UCLASS()
class ABesiegeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	CurrentGameStateEnum CurrentGameState;

	virtual void BeginPlay() override;

	
};

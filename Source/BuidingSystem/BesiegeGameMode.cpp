// Fill out your copyright notice in the Description page of Project Settings.


#include "BesiegeGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ABesiegeGameMode::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState=CurrentGameStateEnum::Placing;
}

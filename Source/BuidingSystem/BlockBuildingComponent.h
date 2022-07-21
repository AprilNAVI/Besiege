// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JointAcotor.h"
#include "PlaceableBase.h"
#include "Components/ActorComponent.h"
#include "BlockBuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUIDINGSYSTEM_API UBlockBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlockBuildingComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	TSubclassOf<class AActor> DefaultBuildingComponentClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	TSubclassOf<class AActor> CurrentBuildingComponentClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	AActor* CurrenBuildingComponentInstance;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	APlaceableBase* SelectedBlock;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	FHitResult CrossHairHitResult;

	FVector TraceStartPoint;
	
	FVector TraceEndPoint;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsPreviewing;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsSpawnReset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsHitBlock;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=Buiding)
	bool bIsBlockRotaionReset;

	FHitResult BuildTrace();

	APlaceableBase* SelectBlock();

	UFUNCTION(BlueprintCallable)
	void OnBuiding();

	UFUNCTION(BlueprintCallable)
	void OnPreview();

	UFUNCTION(BlueprintCallable)
	void DeleteBlock();

	UFUNCTION(BlueprintCallable)
	AJointAcotor* SpawnConstrainActor(AActor* Parent, AActor* Child);

	AActor* SpawnActorByClass(TSubclassOf<AActor> ActorClass);



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BlockAddRotation(float val);

	void ResetBlockRotaion();

		
};

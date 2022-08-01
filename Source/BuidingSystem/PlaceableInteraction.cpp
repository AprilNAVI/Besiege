// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableInteraction.h"

APlaceableInteraction::APlaceableInteraction()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ShellMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));
	
	StaticMesh->SetupAttachment(RootComponent);
	ShellMesh->SetupAttachment(StaticMesh);
	DefaultMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("DefaultMaterial"));
	PreviewMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("PreviewMaterial"));
	ShellMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("ShellMaterial"));
	BlockDistance=50.f;
	PresetMass=100.f;
}

void APlaceableInteraction::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetMaterial(0,PreviewMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	ShellMesh->SetVisibility(false);
	ShellMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APlaceableInteraction::Onplaced()
{
	StaticMesh->SetMaterial(0,DefaultMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMassOverrideInKg(NAME_None,PresetMass,true);
}

UPrimitiveComponent* APlaceableInteraction::GetBlockJointComponent()
{
	return StaticMesh;
}

UPrimitiveComponent* APlaceableInteraction::GetCollisionComponent()
{
	return StaticMesh;
}

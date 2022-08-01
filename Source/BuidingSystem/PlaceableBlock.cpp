// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableBlock.h"

// Sets default values
APlaceableBlock::APlaceableBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("Scene"));
	ShellMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));

	
	RootComponent=BoxComponent;
	StaticMesh->SetupAttachment(BoxComponent);
	ShellMesh->SetupAttachment(StaticMesh);
	DefaultMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("DefaultMaterial"));
	PreviewMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("PreviewMaterial"));
	ShellMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("ShellMaterial"));
	BlockDistance=200.f;
	
}

// Called when the game starts or when spawned
void APlaceableBlock::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetBoxExtent(FVector(BlockDistance/2));
	StaticMesh->SetMaterial(0,PreviewMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ShellMesh->SetVisibility(false);
	ShellMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void APlaceableBlock::Onplaced()
{
	StaticMesh->SetMaterial(0,DefaultMaterial);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetMassOverrideInKg(NAME_None,PresetMass,true);
	//
}

UPrimitiveComponent* APlaceableBlock::GetBlockJointComponent()
{
	return Super::GetBlockJointComponent();
}

UPrimitiveComponent* APlaceableBlock::GetCollisionComponent()
{
	return BoxComponent;
}

void APlaceableBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}





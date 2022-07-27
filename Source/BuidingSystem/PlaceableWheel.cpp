// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableWheel.h"

#include "Kismet/KismetMathLibrary.h"

APlaceableWheel::APlaceableWheel()
{
	
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ShellMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));

	RootComponent=StaticMesh;
	ShellMesh->SetupAttachment(StaticMesh);
	DefaultMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("DefaultMaterial"));
	PreviewMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("PreviewMaterial"));
	ShellMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("ShellMaterial"));
	BlockDistance=50.f;
	PresetMass=100.f;


}

void APlaceableWheel::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetMaterial(0,PreviewMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	ShellMesh->SetRelativeScale3D(StaticMesh->GetRelativeScale3D());
	ShellMesh->SetVisibility(false);
	ShellMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void APlaceableWheel::Onplaced()
{
	StaticMesh->SetMaterial(0,DefaultMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMassOverrideInKg(NAME_None,PresetMass,true);
	
}



UPrimitiveComponent* APlaceableWheel::GetBlockJointComponent()
{
	return StaticMesh;
}

void APlaceableWheel::ReserverRotation(bool IsRightEqualCoreRight)
{
	if (IsRightEqualCoreRight)
	{
		GetBlockJointComponent()->AddRelativeRotation(FRotator(0.f,0.f,0.f));
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Green,FString("use the right direction as the core"));
		
	}
	else
	{
		GetBlockJointComponent()->AddRelativeRotation(FRotator(0.f,180.f,0.f));
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Green,FString(" use the left direction as the core"));
	}
}


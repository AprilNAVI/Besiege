// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableTurnWheel.h"

#include "JointActor.h"

APlaceableTurnWheel::APlaceableTurnWheel()
{
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxSceneComponent"));
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ShellMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));


	StaticMesh->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);
	ShellMesh->SetupAttachment(StaticMesh);
	DefaultMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("DefaultMaterial"));
	PreviewMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("PreviewMaterial"));
	ShellMaterial=CreateDefaultSubobject<UMaterialInterface>(TEXT("ShellMaterial"));
	BlockDistance=50.f;
	PresetMass=100.f;
}

void APlaceableTurnWheel::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetMaterial(0,PreviewMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	ShellMesh->SetRelativeScale3D(StaticMesh->GetRelativeScale3D());
	ShellMesh->SetVisibility(false);
	ShellMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);

	const FActorSpawnParameters SpawnParameters;
	AJointActor* JointAcotor=GetWorld()->SpawnActor<AJointActor>(AJointActor::StaticClass(),StaticMesh->GetComponentLocation(),FRotator(0.f),SpawnParameters);
	JointAcotor->ConstructStrongConstraint(ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Locked,0.f);
	JointAcotor->ReInitConstaintCompont(BoxComponent,StaticMesh);
}

void APlaceableTurnWheel::Onplaced()
{
	StaticMesh->SetMaterial(0,DefaultMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMassOverrideInKg(NAME_None,PresetMass,true);

	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetMassOverrideInKg(NAME_None,0,true);
}

UPrimitiveComponent* APlaceableTurnWheel::GetBlockJointComponent()
{
	return BoxComponent;
}

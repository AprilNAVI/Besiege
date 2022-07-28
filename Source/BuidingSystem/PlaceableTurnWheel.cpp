// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableTurnWheel.h"

#include "JointActor.h"
#include "Kismet/KismetMathLibrary.h"

APlaceableTurnWheel::APlaceableTurnWheel()
{
	PhysicsConstraintComponent=CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("SelfJoint"));
	AxisMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxisMesh"));

	RootComponent=StaticMesh;
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
	
	
	AxisMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	

}

void APlaceableTurnWheel::Onplaced()
{
	StaticMesh->SetMaterial(0,DefaultMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMassOverrideInKg(NAME_None,PresetMass,true);

	AxisMesh->SetWorldLocation(StaticMesh->GetComponentLocation());
	AxisMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	AxisMesh->SetSimulatePhysics(true);
	AxisMesh->SetMassOverrideInKg(NAME_None,PresetMass,true);

	
	FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),GetActorLocation()+GetActorForwardVector());
	PhysicsConstraintComponent->SetWorldLocation(GetActorLocation());
	PhysicsConstraintComponent->SetWorldRotation(LookAtRotation);
	PhysicsConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked,0.f);
	PhysicsConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked,0.f);
	PhysicsConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free,0);
	PhysicsConstraintComponent->SetConstrainedComponents(AxisMesh,FName(),StaticMesh,FName());

	/*
	*	const FActorSpawnParameters SpawnParameters;
	*	AJointActor* JointAcotor=GetWorld()->SpawnActor<AJointActor>(AJointActor::StaticClass(),BoxComponent->GetComponentLocation(),FRotator(0.f),SpawnParameters);
	JointAcotor->SetActorRotation(LookAtRotation);
	JointAcotor->ConstructStrongConstraint(ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Free,0.f);
	JointAcotor->SetLinearBreakable(false,0.f);
	JointAcotor->SetLinearPlasticity(false,0.f);
	JointAcotor->SetAngularBreakable(false,0.f);
	JointAcotor->SetAngularPlasticity(false,0.f);
	JointAcotor->ReInitConstaintCompont(StaticMesh,BoxComponent);

	*/
	
}

UPrimitiveComponent* APlaceableTurnWheel::GetBlockJointComponent()
{
	return AxisMesh;
}

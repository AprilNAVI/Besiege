// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableTurnWheel.h"

#include "JointActor.h"
#include "Kismet/KismetMathLibrary.h"

APlaceableTurnWheel::APlaceableTurnWheel()
{
	PhysicsConstraintComponent=CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("SelfJoint"));
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

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

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);

}

void APlaceableTurnWheel::Onplaced()
{
	Super::Onplaced();

	BoxComponent->SetWorldLocation(StaticMesh->GetComponentLocation());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetMassOverrideInKg(NAME_None,0,true);
	
	const FActorSpawnParameters SpawnParameters;
	AJointActor* JointAcotor=GetWorld()->SpawnActor<AJointActor>(AJointActor::StaticClass(),BoxComponent->GetComponentLocation(),FRotator(0.f),SpawnParameters);
	FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),GetActorLocation()+GetActorForwardVector());
	JointAcotor->SetActorRotation(LookAtRotation);
	JointAcotor->ConstructStrongConstraint(ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Locked,0.f,ECustomAngularConstraintMotion::Free,0.f);
	JointAcotor->SetLinearBreakable(false,0.f);
	JointAcotor->SetLinearPlasticity(false,0.f);
	JointAcotor->SetAngularBreakable(false,0.f);
	JointAcotor->SetAngularPlasticity(false,0.f);
	JointAcotor->ReInitConstaintCompont(BoxComponent,StaticMesh);

	/*
	PhysicsConstraintComponent->SetWorldLocation(GetActorLocation());
	PhysicsConstraintComponent->SetWorldRotation(LookAtRotation);
	PhysicsConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked,0.f);
	PhysicsConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked,0.f);
	PhysicsConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free,0);
	PhysicsConstraintComponent->SetConstrainedComponents(BoxComponent,FName(),StaticMesh,FName());
	*/
	
}

UPrimitiveComponent* APlaceableTurnWheel::GetBlockJointComponent()
{
	return BoxComponent;
}

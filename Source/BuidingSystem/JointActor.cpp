// Fill out your copyright notice in the Description page of Project Settings.


#include "JointActor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values

AJointActor::AJointActor()
{
	
	ConstraintComp=CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Joint"));
	ArrowComponent=CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent=ConstraintComp;
	ArrowComponent->SetupAttachment(ConstraintComp);

}

// Called when the game starts or when spawned
void AJointActor::BeginPlay()
{
	Super::BeginPlay();

	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetVisibility(true);
	this->SetHidden(false);
	ArrowComponent->SetRelativeScale3D(FVector(3.f));
}


void AJointActor::PostLoad()
{
	Super::PostLoad();

}


void AJointActor::ReInitConstaintCompont(UPrimitiveComponent* Component1,UPrimitiveComponent* Component2)
{
	if (Component1!=nullptr&&Component2!=nullptr)
	{
		ConstraintComp->SetConstrainedComponents(Component1,FName(),Component2,FName());
		UE_LOG(LogTemp,Warning,TEXT("ReInitConstaintCompont Succeed!"));
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("ReInitConstaintCompont Failed!"));
	}
}

void AJointActor::SetLinearBreakable(bool IsLinearBreakable, float LinearBreakThreshold)
{
	ConstraintComp->SetLinearBreakable(IsLinearBreakable,LinearBreakThreshold);
}

void AJointActor::SetAngularBreakable(bool IsAngularBreakable, float AngularBreakThreshold)
{
	ConstraintComp->SetAngularBreakable(IsAngularBreakable,AngularBreakThreshold);
}

void AJointActor::SetLinearPlasticity(bool IsAngularPlasticity, float LinearPlasticityThreshold)
{
	ConstraintComp->SetLinearPlasticity(IsAngularPlasticity,LinearPlasticityThreshold);
}

void AJointActor::SetAngularPlasticity(bool IsAngularPlasticity, float AngularPlasticityThreshold)
{
	ConstraintComp->SetAngularPlasticity(IsAngularPlasticity,AngularPlasticityThreshold);
}

void AJointActor::ConstructStrongConstraint(ECustomAngularConstraintMotion Swing1Limit,float Angle1,ECustomAngularConstraintMotion Swing2Limit,float Angle2,ECustomAngularConstraintMotion TwistLimit,float Twist)
{
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Green,FString("ConstructStrongConstraint"));
	ConstraintComp->SetAngularSwing1Limit(static_cast<EAngularConstraintMotion>(Swing1Limit),Angle1);
	ConstraintComp->SetAngularSwing2Limit(static_cast<EAngularConstraintMotion>(Swing2Limit),Angle2);
	ConstraintComp->SetAngularTwistLimit(static_cast<EAngularConstraintMotion>(TwistLimit),Twist);
}

void AJointActor::SetAngularDriveMode(ECustomAngularDriveMode DriveMode)
{
	ConstraintComp->SetAngularDriveMode(static_cast<EAngularDriveMode::Type>(DriveMode));
}

void AJointActor::SetAngularOrientationDrive(bool bEnableSwingDrive, bool bEnableTwistDrive)
{
	ConstraintComp->SetAngularOrientationDrive(bEnableSwingDrive,bEnableTwistDrive);
}

void AJointActor::SetAngularOrientationTarget(const FRotator& InPosTarget)
{
	ConstraintComp->SetAngularOrientationTarget(InPosTarget);
}

void AJointActor::SetAngularVelocityTarget(const FVector& InVelTarget)
{
	ConstraintComp->SetAngularVelocityTarget(InVelTarget);
}

void AJointActor::SetAngularDriveParams(float PositionStrength, float VelocityStrength, float InForceLimit)
{
	ConstraintComp->SetAngularDriveParams(PositionStrength,VelocityStrength,InForceLimit);
}

void AJointActor::SetAngularVelocityDriveTwistAndSwing(bool bEnableTwistDrive, bool bEnableSwingDrive)
{
	ConstraintComp->SetAngularVelocityDriveTwistAndSwing(bEnableTwistDrive,bEnableSwingDrive);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "JointAcotor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AJointAcotor::AJointAcotor()
{
	
	ConstraintComp=CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Joint"));
	RootComponent=ConstraintComp;

}

// Called when the game starts or when spawned
void AJointAcotor::BeginPlay()
{
	Super::BeginPlay();

}


void AJointAcotor::PostLoad()
{
	Super::PostLoad();

}


void AJointAcotor::ReInitConstaintCompont(UPrimitiveComponent* Component1,UPrimitiveComponent* Component2)
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

void AJointAcotor::ConstructStrongConstraint(ECustomAngularConstraintMotion Swing1Limit,float Angle1,ECustomAngularConstraintMotion Swing2Limit,float Angle2,ECustomAngularConstraintMotion TwistLimit,float Twist)
{
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Green,FString("ConstructStrongConstraint"));
	ConstraintComp->SetAngularSwing1Limit(static_cast<EAngularConstraintMotion>(Swing1Limit),Angle1);
	ConstraintComp->SetAngularSwing2Limit(static_cast<EAngularConstraintMotion>(Swing2Limit),Angle2);
	ConstraintComp->SetAngularTwistLimit(static_cast<EAngularConstraintMotion>(TwistLimit),Twist);
}

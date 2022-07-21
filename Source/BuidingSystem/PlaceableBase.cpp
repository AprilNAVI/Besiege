// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableBase.h"

// Sets default values
APlaceableBase::APlaceableBase()
{

	Swing1Limit=ECustomAngularConstraintMotion::Free;
	Swing2Limit=ECustomAngularConstraintMotion::Free;
	TwistLimit=ECustomAngularConstraintMotion::Free;
	Angle1=0.0f;
	Angle2=0.0f;
	TwistAngle=0.0f;
}



void APlaceableBase::Onplaced()
{
}

UPrimitiveComponent* APlaceableBase::GetBlockJointComponent()
{
	return BoxComponent;
}

FVector APlaceableBase::GetCollisonWorldLocation()
{
	return GetBlockJointComponent()->GetComponentLocation();
}

FVector APlaceableBase::GetCoreForward()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetCoreForward();
	}
	else
	{
		return GetActorForwardVector();
	}
	
}

FVector APlaceableBase::GetCoreRight()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetCoreRight();
	}
	else
	{
		return GetActorRightVector();
	}
}

FVector APlaceableBase::GetCoreUp()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetCoreUp();
	}
	else
	{
		return GetActorUpVector();
	}
}

// Called when the game starts or when spawned
void APlaceableBase::BeginPlay()
{
	Super::BeginPlay();
	
}


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

	bIsLinearBreakable=false;
	LinearBreakThreshold=0.f;
	bIsAngularBreakable=false;
	AngularBreakThreshold=0.f;

	bIsLinearPlasticity=false;
	LinearPlasticityThreshold=0.f;
	bIsAngularPlasticity=false;
	AngularPlasticityThreshold=0.f;
	
}



void APlaceableBase::Onplaced()
{
}

void APlaceableBase::OnSelected()
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic= ShellMesh->CreateDynamicMaterialInstance(0,ShellMaterial);
	if (MaterialInstanceDynamic)
	{
		ShellMesh->SetMaterial(0,MaterialInstanceDynamic);
		ShellMesh->SetVisibility(true);
	}
}

void APlaceableBase::OnCancelSelected()
{
	ShellMesh->SetVisibility(false);
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

FRotator APlaceableBase::GetCoreRotation()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetCoreRotation();
	}
	else
	{
		return GetActorRotation();
	}
}

FVector APlaceableBase::GetCoreLocation()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetCoreLocation();
	}
	else
	{
		return GetActorLocation();
	}
}

float APlaceableBase::GetWholeMass()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetWholeMass();
	}
	else
	{
		return TheWholeMass;
	}
}

int APlaceableBase::GetComponentNums()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		return Cast<APlaceableBase>(ParentBlock)->GetWholeMass();
	}
	else
	{
		return TheComponentNum;
	}
}

void APlaceableBase::AddWholeMass(float Mass)
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		ParentBlock->AddWholeMass(Mass);
	}
	else
	{
		TheWholeMass+=Mass;
	}
}

void APlaceableBase::AddComponentNums()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		ParentBlock->AddComponentNums();
	}
	else
	{
		TheComponentNum++;
	}
}

void APlaceableBase::ReduceComponentNums()
{
	if (Cast<APlaceableBase>(ParentBlock))
	{
		AddComponentNums();
	}
	else
	{
		TheComponentNum--;
	}
}

// Called when the game starts or when spawned
void APlaceableBase::BeginPlay()
{
	Super::BeginPlay();

	TheWholeMass=PresetMass;
	TheComponentNum=1;
	ComponentLevel=0;
}



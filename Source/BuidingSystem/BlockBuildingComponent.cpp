// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBuildingComponent.h"

#include "PlaceableTurnWheel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBlockBuildingComponent::UBlockBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsAutoJoint=false;
}

// Called when the game starts
void UBlockBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	bIsPreviewing=false;
	bIsSpawnReset=true;
	bIsHitBlock=false;
	bIsBlockRotaionReset=true;
	
}

FHitResult UBlockBuildingComponent::BuildTrace()
{
	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStartPoint,TraceEndPoint,ETraceTypeQuery::TraceTypeQuery1,
		false,IgnoreActors,EDrawDebugTrace::ForOneFrame,HitResult,true);
	if (Cast<APlaceableBase>(HitResult.GetActor()))
	{
		bIsHitBlock=true;
	}
	else
	{
		bIsHitBlock=false;
	}
	return  HitResult;
}

APlaceableBase* UBlockBuildingComponent::SelectBlock()
{
	APlaceableBase* Block=Cast<APlaceableBase>(CrossHairHitResult.GetActor());
	if (Block)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,"SelectBlock!");
		return Block;
	}
	else
	{
		if (SelectedBlock)
		{
			SelectedBlock->OnCancelSelected();
			SelectedBlock=nullptr;
		}
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Blue,FString("SelectBlock Failed!"));
		return nullptr;
	}
}

void UBlockBuildingComponent::OnBuidingAndSelect()
{
	if (bIsPreviewing)
	{
		OnBuiding();
	}
	else
	{
		OnSelect();
	}
}

void UBlockBuildingComponent::OnBuiding()
{
	if (CurrenBuildingComponentInstance)
	{
		APlaceableTurnWheel* TurnWheel=Cast<APlaceableTurnWheel>(CurrenBuildingComponentInstance);
		if (TurnWheel)
		{
			TurnWheel->Onplaced();
			if (bIsHitBlock)
			{
				FVector SpawnLocation=TurnWheel->GetActorLocation();
				FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(TurnWheel->GetActorLocation(),TurnWheel->GetActorLocation()+TurnWheel->GetCoreUp());
				SpawnConstrainActor(CrossHairHitResult.GetActor(),TurnWheel,LookAtRotation,SpawnLocation);
				Cast<APlaceableBase>(CrossHairHitResult.GetActor())->ChildBlocks.Add(TurnWheel);
				TurnWheel->ParentBlock=Cast<APlaceableBase>(CrossHairHitResult.GetActor());
				TurnWheel->AddWholeMass(TurnWheel->PresetMass);
				TurnWheel->AddComponentNums();
			}
			CurrenBuildingComponentInstance=nullptr;
			bIsPreviewing=false;
			bIsSpawnReset=true;
			return;
		}
		APlaceableBase* PlaceableBase=Cast<APlaceableBase>(CurrenBuildingComponentInstance);
		if (PlaceableBase)
		{
			PlaceableBase->Onplaced();
			if (bIsHitBlock)
			{
				FVector SpawnLocation=(CrossHairHitResult.GetActor()->GetActorLocation()+PlaceableBase->GetActorLocation())/2;
				FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(CrossHairHitResult.GetActor()->GetActorLocation(),CrossHairHitResult.GetActor()->GetActorLocation()+CrossHairHitResult.Normal);
				SpawnConstrainActor(CrossHairHitResult.GetActor(),PlaceableBase,LookAtRotation,SpawnLocation);
				Cast<APlaceableBase>(CrossHairHitResult.GetActor())->ChildBlocks.Add(PlaceableBase);
				PlaceableBase->ParentBlock=Cast<APlaceableBase>(CrossHairHitResult.GetActor());
				PlaceableBase->AddWholeMass(PlaceableBase->PresetMass);
				PlaceableBase->AddComponentNums();
				APlaceableBlock* PlaceableBlock=Cast<APlaceableBlock>(PlaceableBase);
				if (PlaceableBlock)
				{
					BlockAutoJoint(PlaceableBlock);
				}
			}
		}
	}
	CurrenBuildingComponentInstance=nullptr;
	bIsPreviewing=false;
	bIsSpawnReset=true;
}

void UBlockBuildingComponent::BlockAutoJoint(APlaceableBlock* CurrentBlock)
{
	if (bIsAutoJoint)
	{
		FVector TraceStart=CurrentBlock->GetActorLocation();
		TArray<AActor*> IgnoreActors;
		FHitResult HitResult;
		//Forward
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorForwardVector()*100,ETraceTypeQuery::TraceTypeQuery1,
	false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
		//Back
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorForwardVector()*-100,ETraceTypeQuery::TraceTypeQuery1,
false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
		//Right
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorRightVector()*100,ETraceTypeQuery::TraceTypeQuery1,
false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
		//Left
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorRightVector()*-100,ETraceTypeQuery::TraceTypeQuery1,
false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
		//Up
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorUpVector()*100,ETraceTypeQuery::TraceTypeQuery1,
false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
		//Down
		{
			UKismetSystemLibrary::LineTraceSingle(GetWorld(),TraceStart,TraceStart+CurrentBlock->GetActorUpVector()*-100,ETraceTypeQuery::TraceTypeQuery1,
false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
			APlaceableBlock *NearBlock=Cast<APlaceableBlock>(HitResult.GetActor());
			if (NearBlock)
			{
				//SpawnConstrainActor(NearBlock,CurrentBlock);
				Cast<APlaceableBase>(NearBlock)->ChildBlocks.Add(CurrentBlock);
			}
		}
	}
}

void UBlockBuildingComponent::OnSelect()
{
	if (SelectedBlock==nullptr)
	{
		SelectedBlock=SelectBlock();
		if (SelectedBlock)
		{
			SelectedBlock->OnSelected();
			FString DebugMassage=FString("SelectBlock Succeed:  "+SelectedBlock->GetName());
			GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,DebugMassage);
		}
	}
	else
	{
		SelectedBlock->OnCancelSelected();
		SelectedBlock=SelectBlock();
		if (SelectedBlock)
		{
			SelectedBlock->OnSelected();
			FString DebugMassage=FString("SelectBlock Succeed:  "+SelectedBlock->GetName());
			GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,DebugMassage);
		}

	}
}

void UBlockBuildingComponent::OnPreview()
{
	bIsPreviewing=!bIsPreviewing;
	if (SelectedBlock)
	{
		SelectedBlock->OnCancelSelected();
		SelectedBlock=nullptr;
	}
	if (!bIsPreviewing)
	{
		if (CurrenBuildingComponentInstance)
		{
			CurrenBuildingComponentInstance->Destroy();
		}
		bIsSpawnReset=true;
	}
}

void UBlockBuildingComponent::DeleteBlock()
{
	if (SelectedBlock)
	{
		if (SelectedBlock->ParentBlock)
		{
			int index=SelectedBlock->ParentBlock->Children.Find(SelectedBlock);
			if (index!=-1)
			{
				SelectedBlock->ParentBlock->Children.Remove(SelectedBlock->ParentBlock->Children[index]);
			}
			SelectedBlock->ParentBlock->AddWholeMass(-SelectedBlock->PresetMass);
			SelectedBlock->ParentBlock->ReduceComponentNums();
		}
		SelectedBlock->Destroy();
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Blue,FString("Delete Block! "));
	}
}

AJointActor* UBlockBuildingComponent::SpawnConstrainActor(AActor* Parent, AActor* Child,FRotator LookAt,FVector SpawnLocation)
{
	
	const FActorSpawnParameters SpawnParameters;
	AJointActor* JointAcotor=GetWorld()->SpawnActor<AJointActor>(AJointActor::StaticClass(),SpawnLocation,FRotator(0.f),SpawnParameters);
	JointAcotor->SetActorRotation(LookAt);
	JointAcotor->SetConstraintActor1(Parent);
	JointAcotor->SetConstraintActor2(Child);
	APlaceableBase* CurrentBlock=Cast<APlaceableBase>(Child);
	if (Cast<APlaceableBase>(JointAcotor->GetConstraintActor1())&&Cast<APlaceableBase>(JointAcotor->GetConstraintActor2()))
	{
		JointAcotor->ConstructStrongConstraint(CurrentBlock->Swing1Limit,CurrentBlock->Angle1,CurrentBlock->Swing2Limit,CurrentBlock->Angle2,CurrentBlock->TwistLimit,CurrentBlock->TwistAngle);
		JointAcotor->SetLinearBreakable(CurrentBlock->bIsLinearBreakable,CurrentBlock->LinearBreakThreshold);
		JointAcotor->SetLinearPlasticity(CurrentBlock->bIsLinearPlasticity,CurrentBlock->LinearPlasticityThreshold);
		JointAcotor->SetAngularBreakable(CurrentBlock->bIsAngularBreakable,CurrentBlock->AngularBreakThreshold);
		JointAcotor->SetAngularPlasticity(CurrentBlock->bIsAngularPlasticity,CurrentBlock->AngularPlasticityThreshold);
		JointAcotor->SetAngularDriveMode(CurrentBlock->AngularDriveMode);
		JointAcotor->SetAngularOrientationTarget(CurrentBlock->PosTarget);
		JointAcotor->SetAngularOrientationDrive(CurrentBlock->bOrientationEnableSwingDrive,CurrentBlock->bOrientationEnableTwistDrive);
		JointAcotor->SetAngularVelocityTarget(CurrentBlock->VelocityTarget);
		JointAcotor->SetAngularVelocityDriveTwistAndSwing(CurrentBlock->bVelocityEnableSwingDrive,CurrentBlock->bVelocityEnableTwistDrive);
		JointAcotor->SetAngularDriveParams(CurrentBlock->PositionStrength,CurrentBlock->VelocityStrength,CurrentBlock->MaxForce);
		
		JointAcotor->ReInitConstaintCompont(Cast<APlaceableBase>(JointAcotor->GetConstraintActor1())->GetBlockJointComponent(),Cast<APlaceableBase>(JointAcotor->GetConstraintActor2())->GetBlockJointComponent());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Blue,FString("SpawnConstrainActor Failed!"));
		UE_LOG(LogTemp,Log,TEXT("SpawnConstrainActor Failed!"));
	}
	return JointAcotor;
}

AActor* UBlockBuildingComponent::SpawnActorByClass(TSubclassOf<AActor> ActorClass)
{
	FRotator(0.f,0.f,0.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* TempActor= GetWorld()->SpawnActor<AActor>(ActorClass,FVector(0.f),FRotator(0.f),SpawnParameters);
	return TempActor;
}

void UBlockBuildingComponent::BlockAddRotation(float val)
{
	if (CurrenBuildingComponentInstance)
	{
		FVector Aixs=UKismetMathLibrary::InverseTransformDirection(CurrenBuildingComponentInstance->GetActorTransform(),CurrenBuildingComponentInstance->GetActorForwardVector());
		FRotator NewRotaion=UKismetMathLibrary::RotatorFromAxisAndAngle(Aixs,val * 45.f * GetWorld()->GetDeltaSeconds());
		CurrenBuildingComponentInstance->AddActorLocalRotation(FRotator(NewRotaion));
	}
}

void UBlockBuildingComponent::ResetBlockRotaion()
{
	if (bIsBlockRotaionReset)
	{
		FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(FVector(0.f),CrossHairHitResult.Normal);
		CurrenBuildingComponentInstance->SetActorRotation(LookAtRotation);
		if (Cast<APlaceableWheel>(CurrenBuildingComponentInstance))
		{
			APlaceableWheel* CurrenBuildingWheel=Cast<APlaceableWheel>(CurrenBuildingComponentInstance);
			bool bIsRightEqualCoreRight=UKismetMathLibrary::EqualEqual_VectorVector(
				CurrenBuildingWheel->GetWheelAxis(),
				Cast<APlaceableBase>(CrossHairHitResult.GetActor())->GetCoreRight(),
				0.1f);
			CurrenBuildingWheel->ReserverRotation(bIsRightEqualCoreRight);
		}
	}
	bIsBlockRotaionReset=false;
}

// Called every frame
void UBlockBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CrossHairHitResult=BuildTrace();
	if (bIsPreviewing)
	{
		if (bIsSpawnReset)
		{
			bIsSpawnReset=false;
			if (CurrentBuildingComponentClass)
			{
				CurrenBuildingComponentInstance= SpawnActorByClass(CurrentBuildingComponentClass);
			}
			else
			{
				CurrenBuildingComponentInstance= SpawnActorByClass(DefaultBuildingComponentClass);
			}
			
		}
		FVector HitResultLocation= CrossHairHitResult.Location;
		//HitResultLocation=UKismetMathLibrary::Vector_SnappedToGrid(HitResultLocation,100.f);
		FVector NewLocation;
		if (bIsHitBlock&&CrossHairHitResult.GetActor())
		{
			FVector HitActorLocation=Cast<APlaceableBase>(CrossHairHitResult.GetActor())->GetBlockJointComponent()->GetComponentLocation();
			FVector normal=CrossHairHitResult.Normal;
			UKismetMathLibrary::Vector_Normalize(CrossHairHitResult.Normal);
			NewLocation=HitActorLocation+normal*Cast<APlaceableBase>(CurrenBuildingComponentInstance)->BlockDistance;
			if (CurrenBuildingComponentInstance)
			{
				CurrenBuildingComponentInstance->SetActorLocation(NewLocation);
				ResetBlockRotaion();
			}
		}
		else
		{
			NewLocation=FVector(HitResultLocation.X,HitResultLocation.Y,HitResultLocation.Z+100.f);
			if (CurrenBuildingComponentInstance)
			{
				CurrenBuildingComponentInstance->SetActorLocation(NewLocation);
				OwnerActorForward.Z=0;
				FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(NewLocation,NewLocation+OwnerActorForward);
				CurrenBuildingComponentInstance->SetActorRotation(LookAtRotation);
				//ResetBlockRotaion();
			}
		}

	}
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

#include "PlaceableWheel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	bIsBuilding=false;
	bIsReset=true;
	bIsHitBlock=false;
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	BlockBuildingComponent=CreateDefaultSubobject<UBlockBuildingComponent>(TEXT("BlockBuildingComponent"));
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	bIsBlockRotaionReset=true;
	Super::BeginPlay();
	BesiegePlayerController=Cast<ABesiegePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
}

void AFPS_Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddActorLocalOffset(FVector(Value * 400.f * GetWorld()->GetDeltaSeconds(),0.f,0.f));
	}
}

void AFPS_Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddActorLocalOffset(FVector(0.f,Value * 400.f * GetWorld()->GetDeltaSeconds(),0.f));
	}
}

void AFPS_Character::Fly(float val)
{
	if (val!=0)
	{
		AddActorWorldOffset(FVector(0.f,0.f,val * 300.f * GetWorld()->GetDeltaSeconds()));
	}
}

void AFPS_Character::CurrentBlockTurnRight()
{
	if (CurrenBuildingComponentInstance)
	{
		FVector Aixs=UKismetMathLibrary::InverseTransformDirection(CurrenBuildingComponentInstance->GetActorTransform(),CurrenBuildingComponentInstance->GetActorForwardVector());
		FRotator NewRotaion=UKismetMathLibrary::RotatorFromAxisAndAngle(Aixs,45.f);
		CurrenBuildingComponentInstance->AddActorLocalRotation(FRotator(NewRotaion));
	}
}

void AFPS_Character::CurrentBlockTurnLeft()
{
	if (CurrenBuildingComponentInstance)
	{
		FVector Aixs=UKismetMathLibrary::InverseTransformDirection(CurrenBuildingComponentInstance->GetActorTransform(),CurrenBuildingComponentInstance->GetActorForwardVector());
		FRotator NewRotaion=UKismetMathLibrary::RotatorFromAxisAndAngle(Aixs,-45.f);
		CurrenBuildingComponentInstance->AddActorLocalRotation(FRotator(NewRotaion));
	}
}


FHitResult AFPS_Character::BuildTrace()
{

	TArray<AActor*> IgnoreActors;
	const FVector Start=FirstPersonCameraComponent->GetComponentLocation();
	const FVector End=Start+FirstPersonCameraComponent->GetForwardVector()*700.f;
	FHitResult HitResult,SecondHitResult;
	bool bIsHit=UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start,End,ETraceTypeQuery::TraceTypeQuery1,
		false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
	FVector TracedLocation=HitResult.Location;
	AActor* HitActor=HitResult.GetActor();
	APlaceableBase* PlaceableBlock=Cast<APlaceableBase>(HitActor);
	if (PlaceableBlock)
	{
		
		FVector Normal=HitResult.Normal;
		UKismetMathLibrary::Vector_Normalize(Normal);
		FString output(
			 "X: "+UKismetStringLibrary::Conv_FloatToString(Normal.X)
			+"Y: "+UKismetStringLibrary::Conv_FloatToString(Normal.Y)
			+"Z: "+UKismetStringLibrary::Conv_FloatToString(Normal.Z));
		//GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Blue,FString("Hit PlaceableBlock "+output));
		bIsHitBlock=true;
	}
	else
	{
		bIsHitBlock=false;
	}
	return  HitResult;
	if (bIsHit)
	{
		UKismetSystemLibrary::LineTraceSingle(GetWorld(),
			FVector(TracedLocation.X,TracedLocation.Y,TracedLocation.Z+200.f),FVector(TracedLocation.X,TracedLocation.Y,TracedLocation.Z-50.f),ETraceTypeQuery::TraceTypeQuery1,
			false,IgnoreActors,EDrawDebugTrace::ForOneFrame,SecondHitResult,true);
		return SecondHitResult;
	}
	else
	{
		UKismetSystemLibrary::LineTraceSingle(GetWorld(),
			FVector(TracedLocation.X,TracedLocation.Y,TracedLocation.Z+200.f),FVector(TracedLocation.X,TracedLocation.Y,TracedLocation.Z-50.f),ETraceTypeQuery::TraceTypeQuery1,
			false,IgnoreActors,EDrawDebugTrace::ForOneFrame,SecondHitResult,true);
		return SecondHitResult;
	}
}

APlaceableBase* AFPS_Character::SelectBlock()
{
	TArray<AActor*> IgnoreActors;
	const FVector Start=FirstPersonCameraComponent->GetComponentLocation();
	const FVector End=Start+FirstPersonCameraComponent->GetForwardVector()*700.f;
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start,End,ETraceTypeQuery::TraceTypeQuery1,
		false,IgnoreActors,EDrawDebugTrace::None,HitResult,true);
	APlaceableBase* Block=Cast<APlaceableBase>(HitResult.GetActor());
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

AJointAcotor* AFPS_Character::SpawnConstrainActor(AActor* Parent, AActor* Child)
{
	FVector SpawnLocation=(Parent->GetActorLocation()+Child->GetActorLocation())/2;
	const FActorSpawnParameters SpawnParameters;
	AJointAcotor* JointAcotor=GetWorld()->SpawnActor<AJointAcotor>(AJointAcotor::StaticClass(),SpawnLocation,FRotator(0.f),SpawnParameters);
	JointAcotor->SetConstraintActor1(Parent);
	JointAcotor->SetConstraintActor2(Child);
	APlaceableBase* CurrentBlock=Cast<APlaceableBase>(Child);
	if (Cast<APlaceableBase>(JointAcotor->GetConstraintActor1())&&Cast<APlaceableBase>(JointAcotor->GetConstraintActor2()))
	{
		JointAcotor->ConstructStrongConstraint(CurrentBlock->Swing1Limit,CurrentBlock->Angle1,CurrentBlock->Swing2Limit,CurrentBlock->Angle2,CurrentBlock->TwistLimit,CurrentBlock->TwistAngle);
		JointAcotor->ReInitConstaintCompont(Cast<APlaceableBase>(JointAcotor->GetConstraintActor1())->GetBlockJointComponent(),Cast<APlaceableBase>(JointAcotor->GetConstraintActor2())->GetBlockJointComponent());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Blue,FString("SpawnConstrainActor Failed!"));
		UE_LOG(LogTemp,Log,TEXT("SpawnConstrainActor Failed!"));
	}
	return JointAcotor;
}

void AFPS_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	//GetCapsuleComponent()->AddRelativeRotation(FRotator(0.f,Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds(),0.f));
}

void AFPS_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPS_Character::OnClick()
{
	if (bIsBuilding)
	{
		if (CurrenBuildingComponentInstance)
		{
			APlaceableBase* PlaceableBase=Cast<APlaceableBase>(CurrenBuildingComponentInstance);
			if (PlaceableBase)
			{
				PlaceableBase->Onplaced();
				if (bIsHitBlock)
				{
					SpawnConstrainActor(CrossHairHitResult.GetActor(),PlaceableBase);
					Cast<APlaceableBase>(CrossHairHitResult.GetActor())->ChildBlocks.Add(CurrenBuildingComponentInstance);
					Cast<APlaceableBase>(CurrenBuildingComponentInstance)->ParentBlock=Cast<APlaceableBase>(CrossHairHitResult.GetActor());
				}
				else
				{

				}
			}
		}
		CurrenBuildingComponentInstance=nullptr;
		bIsBuilding=false;
		bIsReset=true;
	}
	else
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
}

void AFPS_Character::OnBuilding()
{
	bIsBuilding=!bIsBuilding;
	if (SelectedBlock)
	{
		SelectedBlock->OnCancelSelected();
		SelectedBlock=nullptr;
	}
	if (!bIsBuilding)
	{
		if (CurrenBuildingComponentInstance)
		{
			CurrenBuildingComponentInstance->Destroy();
		}
		bIsReset=true;
	}

}

void AFPS_Character::DeleteBlock()
{
	if (SelectedBlock)
	{
		Cast<APlaceableBase>(SelectedBlock)->Destroy();
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Blue,FString("Delete Block! "));
	}
}

AActor* AFPS_Character::SpawnActorByClass(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	FRotator(0.f,0.f,0.f);
	const FActorSpawnParameters SpawnParameters;
	AActor* TempActor= GetWorld()->SpawnActor<AActor>(ActorClass,Transform,SpawnParameters);
	return TempActor;
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsBuilding)
	{
		if (bIsReset)
		{
			bIsReset=false;
			if (CurrentBuildingComponentClass)
			{
				CurrenBuildingComponentInstance= SpawnActorByClass(CurrentBuildingComponentClass,GetActorTransform());
			}
			else
			{
				CurrenBuildingComponentInstance= SpawnActorByClass(DefaultBuildingComponentClass,GetActorTransform());
			}
			
		}
		CrossHairHitResult=BuildTrace();
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
				//ResetBlockRotaion();
			}
		}
		//FVector NewLocation=FVector(HitActorLocation.X,HitActorLocation.Y,HitActorLocation.Z+200.f);

	}
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_Character::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	

	// Bind Mouse event
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &AFPS_Character::OnClick);
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &AFPS_Character::OnBuilding);
	PlayerInputComponent->BindAction("Delete", IE_Pressed, this, &AFPS_Character::DeleteBlock);
	
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_Character::MoveRight);
	PlayerInputComponent->BindAxis("Fly", this, &AFPS_Character::Fly);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AFPS_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPS_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_Character::LookUpAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPS_Character::LookUpAtRate);

	PlayerInputComponent->BindAxis("BlockTurnRate", this, &AFPS_Character::BlockAddRotation);

}

void AFPS_Character::BlockAddRotation(float val)
{
	if (CurrenBuildingComponentInstance)
	{
		FVector Aixs=UKismetMathLibrary::InverseTransformDirection(CurrenBuildingComponentInstance->GetActorTransform(),CurrenBuildingComponentInstance->GetActorForwardVector());
		FRotator NewRotaion=UKismetMathLibrary::RotatorFromAxisAndAngle(Aixs,val * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		CurrenBuildingComponentInstance->AddActorLocalRotation(FRotator(NewRotaion));
	}
}

void AFPS_Character::ResetBlockRotaion()
{
	if (bIsBlockRotaionReset)
	{
		FRotator LookAtRotation= UKismetMathLibrary::FindLookAtRotation(FVector(0.f),CrossHairHitResult.Normal);
		CurrenBuildingComponentInstance->SetActorRotation(LookAtRotation);
		if (Cast<APlaceableWheel>(CurrenBuildingComponentInstance))
		{
			APlaceableWheel* CurrenBuildingWheel=Cast<APlaceableWheel>(CurrenBuildingComponentInstance);
			bool bIsRightEqualCoreRight=UKismetMathLibrary::EqualEqual_VectorVector(
				CurrenBuildingWheel->GetBlockJointComponent()->GetForwardVector(),
				Cast<APlaceableBase>(CrossHairHitResult.GetActor())->GetCoreRight(),
				0.1f);
			CurrenBuildingWheel->ReserverRotation(bIsRightEqualCoreRight);
		}
	}
	bIsBlockRotaionReset=false;
}


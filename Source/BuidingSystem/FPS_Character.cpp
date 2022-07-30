// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"


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
	Super::BeginPlay();
	BesiegePlayerController=Cast<ABesiegePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	BlockBuildingComponent->TraceStartPoint=FirstPersonCameraComponent->GetComponentLocation();
	BlockBuildingComponent->TraceEndPoint=FirstPersonCameraComponent->GetForwardVector()*700.f;
	BlockBuildingComponent->OwnerActorForward=GetActorForwardVector();
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

void AFPS_Character::OnLeftMouseClick()
{
	BlockBuildingComponent->OnBuidingAndSelect();
}

void AFPS_Character::OnRightMouseClick()
{
	BlockBuildingComponent->OnPreview();
}

void AFPS_Character::OnKeyZClick()
{
	BlockBuildingComponent->DeleteBlock();
}

void AFPS_Character::BlockAddRotation(float val)
{
	BlockBuildingComponent->BlockAddRotation(val);
}


// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BlockBuildingComponent->TraceStartPoint=FirstPersonCameraComponent->GetComponentLocation();
	BlockBuildingComponent->TraceEndPoint=BlockBuildingComponent->TraceStartPoint+FirstPersonCameraComponent->GetForwardVector()*2000.f;
	BlockBuildingComponent->OwnerActorForward=GetActorForwardVector();
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
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &AFPS_Character::OnLeftMouseClick);
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &AFPS_Character::OnRightMouseClick);
	PlayerInputComponent->BindAction("Delete", IE_Pressed, this, &AFPS_Character::OnKeyZClick);
	
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

void AFPS_Character::UnbindMouseInput()
{
	InputComponent = CreatePlayerInputComponent();
	InputComponent->ClearActionBindings();
}

void AFPS_Character::UnbindKeyInput()
{
	InputComponent = CreatePlayerInputComponent();
	InputComponent->ClearActionBindings();
}



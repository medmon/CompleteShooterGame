// Copyright © Jodiah Jensen. All Rights Reserved.


#include "ShooterCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	BaseTurnRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;  //camera follows behind character at this distance
	CameraBoom->bUsePawnControlRotation = true;  // keep boom pointing forward relative to character

	// Create a Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false;  // camera does not rotate relative to arm

	//don't rotate when the controller rotates.  Let the controller only affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f,0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("BeginPlay() Called!"));

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			 ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ShooterMappingContext, 0);
		}		
	}
}
/*
 *	Player Input System (old system)
 */
/*
// void AShooterCharacter::MoveForward(float Value)
// {
// 	if ((Controller != nullptr) && (Value != 0.f))
// 	{
// 		//find which way is for4ward
// 		const FRotator Rotation{ Controller->GetControlRotation() };
// 		const FRotator YawRotation{0, Rotation.Yaw, 0 };
//
// 		const FVector Direction{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
// 		AddMovementInput(Direction, Value);
// 	
// 	}
// }
//
// void AShooterCharacter::MoveRight(float Value)
// {
// 	if ((Controller != nullptr) && (Value != 0.f))
// 	{
// 		//find which way is for4ward
// 		const FRotator Rotation{ Controller->GetControlRotation() };
// 		const FRotator YawRotation{0, Rotation.Yaw, 0 };
//
// 		const FVector Direction{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
// 		AddMovementInput(Direction, Value);
// 		
// 	}
//
// }
//
// void AShooterCharacter::TurnAtRate(float Rate)
// {
// 	// calculate delta for this fram from the rate information
// 	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
// }
//
// void AShooterCharacter::LookUpAtRate(float Rate)
// {
// 	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
//
// }
*/

/*
 *	Enhanced Input System
 */

void AShooterCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();

	if ((Controller != nullptr) && ((DirectionValue.X != 0.f) || DirectionValue.Y != 0.f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{0, Rotation.Yaw, 0 };
		
		//find which way is forward
		const FVector ForwardDirection{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		//move forward(backward)
		AddMovementInput(ForwardDirection, DirectionValue.X);

		//find which way is Right
		const FVector RightDirection{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		//move right(left)
		AddMovementInput(RightDirection, DirectionValue.Y);
		
	
	}
}

void AShooterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
	
}

void AShooterCharacter::Jump()
{
	Super::Jump();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
/*
 *	Old Input System method
 */
	
	// PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	// PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	// PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput );
	// PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

/*
 *	Enhanced Input System method
 */
	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction( MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AShooterCharacter::Move);

		EnhancedInputComponent->BindAction( LookAction,
			ETriggerEvent::Triggered,
			this,
			&AShooterCharacter::Look);

		EnhancedInputComponent->BindAction( JumpAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter::Jump);
		
	}	


}
	
	


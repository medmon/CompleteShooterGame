// Copyright © Jodiah Jensen. All Rights Reserved.


#include "ShooterAnimInstance.h"

#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharacter)
	{
		FVector Velocity{ShooterCharacter->GetVelocity()};
		Velocity.Z = 0;
		Speed = Velocity.Size();

		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		bIsAccelerating = ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size()>0.f? true : false;

	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	
}

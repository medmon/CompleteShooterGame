// Copyright © Jodiah Jensen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"


#include "ShooterCharacter.generated.h"

class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
/*
 *	Enhanced Input System
 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* ShooterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* FireAction;
	
	
	void Jump() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void FireWeapon();
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess))
	USpringArmComponent* CameraBoom;

	//camera that follows the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess))
	UCameraComponent* FollowCamera;

	// Base turn rate in degrees per second. Other scaling may affect final turn rate.
	//This is used for turning with the keyboard versus mouselook 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Camera", meta=(AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Combat", meta=(AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Combat", meta=(AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
	
public:

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};

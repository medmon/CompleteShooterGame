// Copyright © Jodiah Jensen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

	void MoveForward(float Value);
	void MoveRight(float Value);

	/**
	 * Called via input to turn at given rate
	 * @param Rate  This is a normalized rate, 1.0 = 100% of the desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to look up/down at given rate
	 * @param Rate  This is a normalized rate, 1.0 = 100% of the desired look rate
	 */
	void LookUpAtRate(float Rate);
	
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Camera", meta=(AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// Base look up/down rate in degrees per second. Other scaling may affect the final look rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Camera",  meta=(AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	
public:

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};

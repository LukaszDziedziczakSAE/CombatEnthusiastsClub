// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Health.h"
#include "Damager.h"
#include "Move.h"
#include "EFightingStyle.h"
#include "Fighter.generated.h"

UENUM(BlueprintType)
enum EFighterSide
{
	None,
	Left,
	Right
};

UCLASS()
class COMBATENTHUSIASTS_API AFighter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFighter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMove> Moves;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString FighterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsBlocking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WalkingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RunningSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EFighterSide> Side;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EFightingStyle> FightingStyle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MoveInputSensitivity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHealth* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADamager* LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADamager* RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADamager* LeftFoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADamager* RightFoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ADamager> Damager;

	UFUNCTION(BlueprintCallable)
	void BeginAttack(int MoveIndex);

	UFUNCTION(BlueprintNativeEvent)
	void PlayAttackAnimation();

	UFUNCTION(BlueprintCallable)
	void CompleteAttack();

	UFUNCTION(BlueprintPure)
	UAnimMontage* GetCurrentAttackMontage();

	UFUNCTION(BlueprintPure)
	float GetCurretAttackDamage();

	UFUNCTION(BlueprintNativeEvent)
	void BeginImpact();

	UFUNCTION(BlueprintCallable)
	void CompleteImpact();

	UFUNCTION(BlueprintCallable)
	void SetIsBlocking(bool Blocking);

	UFUNCTION(BlueprintCallable)
	void SetIsRunning(bool Running);

	UFUNCTION(BlueprintPure)
	bool GetIsBlocking() { return IsBlocking; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D MovementInput;

	UFUNCTION(BlueprintNativeEvent)
	void Death();

	UFUNCTION()
	void DeathComplete();

	UFUNCTION(BlueprintCallable)
	void SetSide(TEnumAsByte<EFighterSide> NewSide) { Side = NewSide; }

	UFUNCTION(BlueprintCallable)
	FString GetFighterName() { return FighterName; }

private:
	UFUNCTION(BlueprintCallable)
	void AddMovement(float Forward);

};

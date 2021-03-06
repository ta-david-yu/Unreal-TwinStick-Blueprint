// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDiedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedEvent, float, NewHealth);

UCLASS(Blueprintable)
class TWINSTICKSHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	float Health = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Character")
	bool IsDead = false;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FCharacterDiedEvent OnCharacterDied;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FHealthChangedEvent OnHealthChanged;

public:
	virtual void CalculateDead();
	
	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateHealth(float delta);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent) override;
#endif

	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

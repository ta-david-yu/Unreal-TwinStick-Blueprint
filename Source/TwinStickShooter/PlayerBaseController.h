// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerBaseController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_API APlayerBaseController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

private:
	void HandleOnSuicideActionPressed();
};

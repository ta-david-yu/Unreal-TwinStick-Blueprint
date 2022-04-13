// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseController.h"
#include "BaseCharacter.h"

void APlayerBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Suicide"), IE_Pressed, this, &APlayerBaseController::HandleOnSuicideActionPressed);
}

void APlayerBaseController::HandleOnSuicideActionPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("SUICIDE PRESSED"));

	APawn* controlledPawn = GetPawn();
	ABaseCharacter* character = Cast<ABaseCharacter>(controlledPawn);
	if (character->IsValidLowLevel())
	{
		character->CalculateHealth(-999);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseController.h"
#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

void APlayerBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Suicide"), IE_Pressed, this, &APlayerBaseController::HandleOnSuicideActionPressed);
	auto& pauseActionBinding = InputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &APlayerBaseController::HandleOnPauseActionPressed);
	pauseActionBinding.bExecuteWhenPaused = true;
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

void APlayerBaseController::HandleOnPauseActionPressed()
{
	if (m_IsGamePaused)
	{
		ResumeGame();
	}
	else
	{
		PauseGame();
	}

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, TEXT("PAUSE PRESSED"));
}

void APlayerBaseController::PauseGame()
{
	// Pause game
	m_CurrentPauseMenuInstance = CreateWidget(GetWorld(), m_PauseMenuType);
	if (m_CurrentPauseMenuInstance->IsValidLowLevel())
	{
		m_CurrentPauseMenuInstance->AddToViewport();
	}
	m_IsGamePaused = true;
	SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	bShowMouseCursor = true;
}

void APlayerBaseController::ResumeGame()
{
	// Resume game
	if (m_CurrentPauseMenuInstance->IsValidLowLevel())
	{
		m_CurrentPauseMenuInstance->RemoveFromViewport();
		m_CurrentPauseMenuInstance = nullptr;
	}
	m_IsGamePaused = false;
	SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	bShowMouseCursor = false;
}
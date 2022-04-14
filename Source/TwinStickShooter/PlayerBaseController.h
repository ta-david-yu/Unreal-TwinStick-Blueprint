// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBaseController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseEvent);

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_API APlayerBaseController : public APlayerController
{
	GENERATED_BODY()
	
public:  
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FPauseEvent OnPaused;
	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FPauseEvent OnResumed;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> m_PauseMenuType;

	UPROPERTY()
	bool m_IsGamePaused = false;

	UPROPERTY()
	UUserWidget* m_CurrentPauseMenuInstance;

private:
	void HandleOnSuicideActionPressed();
	void HandleOnPauseActionPressed();
};

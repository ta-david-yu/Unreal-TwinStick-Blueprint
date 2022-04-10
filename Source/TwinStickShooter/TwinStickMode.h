// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawner.h"
#include "BaseCharacter.h"
#include "TwinStickMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharcterEvent, ABaseCharacter*, character);

UCLASS()
class TWINSTICKSHOOTER_API ATwinStickMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FCharcterEvent OnNewCharcterSpawned;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FCharcterEvent OnCurrentCharcterSet;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinStickMode")
	TSubclassOf<ABaseCharacter> m_PlayerCharacterType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinStickMode")
	ABaseCharacter* m_CurrentPlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinStickMode")
	float m_EnemySpawnInterval = 4.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinStickMode")
	AEnemySpawner* m_EnemySpawner = nullptr;

private:
	float m_SpawnEnemyTimer = 0.0f;

public:
	ATwinStickMode();

	virtual void Tick(float deltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	APawn* TrySpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void SetCurrentPlayerCharacter(ABaseCharacter* character);

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();

private:
	UFUNCTION()
	void HandleOnPlayerCharacterDied();
};

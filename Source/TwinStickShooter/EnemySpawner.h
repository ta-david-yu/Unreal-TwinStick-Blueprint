// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemySpawner.generated.h"

UCLASS(Blueprintable)
class TWINSTICKSHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APawn> SpawnPawnType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* SpawnVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxEnemyCountInLevel = 16;

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

private:
	int m_EnemyCounter = 0;

	UFUNCTION()
	void HandleOnEnemyDied()
	{
		m_EnemyCounter--;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual APawn* SpawnEnemy();
};

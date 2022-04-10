// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ATwinStickMode::ATwinStickMode()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATwinStickMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	m_SpawnEnemyTimer += deltaTime;
	if (m_SpawnEnemyTimer >= m_EnemySpawnInterval)
	{
		m_SpawnEnemyTimer -= m_EnemySpawnInterval;
		TrySpawnEnemy();
	}
}

void ATwinStickMode::BeginPlay()
{
	Super::BeginPlay();
}

APawn* ATwinStickMode::TrySpawnEnemy()
{
	APawn* pawn = m_EnemySpawner->SpawnEnemy();
	return pawn;
}

void ATwinStickMode::SetCurrentPlayerCharacter(ABaseCharacter* character)
{
	m_CurrentPlayerCharacter = character;
	m_CurrentPlayerCharacter->OnCharacterDied.AddDynamic(this, &ATwinStickMode::HandleOnPlayerCharacterDied);
}

void ATwinStickMode::RespawnPlayer()
{
	if (m_PlayerCharacterType.Get() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Character Type is None, No player is spawned"));
		return;
	}

	UWorld* world = GetWorld();
	int playerIndex = 0;
	APlayerController* playerController = UGameplayStatics::GetPlayerController(world, playerIndex);

	// Spawn
	AActor* playerStartActor = FindPlayerStart(playerController);
	FTransform playerStartTransform = playerStartActor->GetTransform();

	FActorSpawnParameters spawnParams{ };
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ABaseCharacter* newPlayerCharacter = Cast<ABaseCharacter>(GetWorld()->SpawnActor(m_PlayerCharacterType, &playerStartTransform, spawnParams));

	// Posses
	playerController->Possess(newPlayerCharacter);

	// Set to current
	SetCurrentPlayerCharacter(newPlayerCharacter);
}

void ATwinStickMode::HandleOnPlayerCharacterDied()
{
	// Destroy player
	if (m_CurrentPlayerCharacter)
	{
		m_CurrentPlayerCharacter->Destroy();
	}

	// Respawn player
	RespawnPlayer();
}
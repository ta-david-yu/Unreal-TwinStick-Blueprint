// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCharacter.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(FName("Spawn Volume"));


	SetRootComponent(RootComponent);
	SpawnVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

APawn* AEnemySpawner::SpawnEnemy()
{
	if (m_EnemyCounter >= MaxEnemyCountInLevel)
	{
		return nullptr;
	}

	auto volumeWorldLocation = SpawnVolume->GetComponentLocation();
	auto volumeExtent = SpawnVolume->GetScaledBoxExtent();
	auto newSpawnPosition = UKismetMathLibrary::RandomPointInBoundingBox(volumeWorldLocation, volumeExtent);

	ABaseCharacter* const newSpawnedEnemy = Cast<ABaseCharacter>(GetWorld()->SpawnActor(SpawnPawnType, &newSpawnPosition));
	if (newSpawnedEnemy)
	{
		m_EnemyCounter++;
		newSpawnedEnemy->SpawnDefaultController();
		newSpawnedEnemy->OnCharacterDied.AddDynamic(this, &AEnemySpawner::HandleOnEnemyDied);
	}

	return newSpawnedEnemy;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "OnProjectileHitEffect.h"

// Sets default values for this component's properties
UOnProjectileHitEffect::UOnProjectileHitEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOnProjectileHitEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOnProjectileHitEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOnProjectileHitEffect::HandleOnHit()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("On Hit!"));
}


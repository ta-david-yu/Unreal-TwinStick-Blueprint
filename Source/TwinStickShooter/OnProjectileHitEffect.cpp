// Fill out your copyright notice in the Description page of Project Settings.


#include "OnProjectileHitEffect.h"

void UOnProjectileHitEffect::HandleOnHit()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, TEXT("On Hit!"));
}


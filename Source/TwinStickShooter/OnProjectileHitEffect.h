// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OnProjectileHitEffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TWINSTICKSHOOTER_API UOnProjectileHitEffect : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void HandleOnHit();
};

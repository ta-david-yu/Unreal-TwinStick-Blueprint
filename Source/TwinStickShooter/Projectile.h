// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitEvent);

UCLASS()
class TWINSTICKSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = -20;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DamageTag = TEXT("Enemy");

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FHitEvent OnProjectileHit;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
};

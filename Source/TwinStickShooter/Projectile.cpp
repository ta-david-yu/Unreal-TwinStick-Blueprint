// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Damageable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);
	
	bool isDamageable = UKismetSystemLibrary::DoesImplementInterface(otherActor, UDamageable::StaticClass());

	if (!isDamageable)
	{
		// Hit non-damageable actor, destroy the projectile
		OnProjectileHit.Broadcast();
		this->Destroy();
		return;
	}

	bool hasDamageTag = otherActor->ActorHasTag(DamageTag);
	if (hasDamageTag)
	{
		// Hit damageable actor with the damage tag, damage it & destroy the projectile
		IDamageable::Execute_AffectHealth(otherActor, Damage);
		OnProjectileHit.Broadcast();
		this->Destroy();
		return;
	}
}

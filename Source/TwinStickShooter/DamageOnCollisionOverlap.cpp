// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageOnCollisionOverlap.h"
#include "Damageable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UDamageOnCollisionOverlap::UDamageOnCollisionOverlap()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageOnCollisionOverlap::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UDamageOnCollisionOverlap::HandleOnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UDamageOnCollisionOverlap::HandleOnOverlapEnd);
}

void UDamageOnCollisionOverlap::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UDamageOnCollisionOverlap::HandleOnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.RemoveDynamic(this, &UDamageOnCollisionOverlap::HandleOnOverlapEnd);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UDamageOnCollisionOverlap::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> actorsToBeDamaged;

	for (auto& targetSetPair : m_OverlappedTargetSets)
	{
		targetSetPair.Value.Timer += DeltaTime;

		float interval = GetAttakInterval();
		if (targetSetPair.Value.Timer > interval)
		{
			targetSetPair.Value.Timer -= interval;
			actorsToBeDamaged.Add(targetSetPair.Value.Actor);
		}
	}

	for (auto i = 0; i < actorsToBeDamaged.Num(); i++)
	{
		IDamageable::Execute_AffectHealth(actorsToBeDamaged[i], Damage);
	}
}

void UDamageOnCollisionOverlap::HandleOnOverlapBegin
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	bool isDamageable = UKismetSystemLibrary::DoesImplementInterface(OtherActor, UDamageable::StaticClass());

	if (!isDamageable)
	{
		return;
	}

	bool hasDamageTag = OtherActor->ActorHasTag(DamageTag);
	if (hasDamageTag)
	{
		TargetSet targetSet {};
		targetSet.Actor = OtherActor;

		m_OverlappedTargetSets.Add(OtherActor->GetUniqueID(), targetSet);
		return;
	}
}

void UDamageOnCollisionOverlap::HandleOnOverlapEnd
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	m_OverlappedTargetSets.Remove(OtherActor->GetUniqueID());
}


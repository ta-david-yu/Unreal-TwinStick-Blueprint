// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
#include "DamageOnCollisionOverlap.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TWINSTICKSHOOTER_API UDamageOnCollisionOverlap : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPrimitiveComponent* CollisionComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = -20;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DamageTag = "Player";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackPerSecond = 2;

	inline float GetAttakInterval() const { return 1.0f / AttackPerSecond; }

public:	
	// Sets default values for this component's properties
	UDamageOnCollisionOverlap();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	struct TargetSet
	{
		AActor* Actor;
		float Timer;
	};

	TMap<uint32, TargetSet> m_OverlappedTargetSets;

	UFUNCTION()
	void HandleOnOverlapBegin
	(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void HandleOnOverlapEnd
	(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
		
};

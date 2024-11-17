// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class CPP_TSUBCLASSOFF_API ATeleporter : public AActor
{
	GENERATED_BODY()

public:
	ATeleporter();

	//TARGET TELEPORTER
	UPROPERTY(EditInstanceOnly, Category = "Teleporter")
	ATeleporter* TargetTeleporter;

	FVector GetTeleportPoint();
	void OnTeleport();

protected:
	virtual void BeginPlay() override;

	//ACTOR ENTERS THE TRIGGER
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
	//ALLOWED ACTORS
	UPROPERTY(EditAnywhere, Category = "Teleporter")
	TArray<TSubclassOf<AActor>> EnabledClass;

	//PARTICLES
	UPROPERTY(VisibleAnywhere, Category = "Teleporter")
	UParticleSystemComponent* TeleportEffect;

	//SOUND
	UPROPERTY(VisibleAnywhere, Category = "Teleporter")
	UAudioComponent* TeleportSound;
	
	//MESH
	UPROPERTY(EditAnywhere, Category = "Teleport")
	UStaticMeshComponent* TeleportMesh;

	//COLISSION TO DETECT ENTRY
	UPROPERTY(EditDefaultsOnly, Category = "Teleporter")
	class UBoxComponent* TeleportTrigger;

	//TARGET LOCATION OF THE TELEPORT
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	USceneComponent* TeleportPoint;

	//VARIABLE TO AVOID LOOPS
	bool CanTeleport;

	//FADE FUNCTION
	void PerformFade(AActor* PlayerActor);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
public:
	virtual void Tick(float DeltaTime) override;
};


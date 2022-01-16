// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RandomMesh.generated.h"

UCLASS()
class UE_MULTIPLAYER_API ARandomMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "MovingPlatform")
		UStaticMeshComponent* RandomMesh;

	UPROPERTY(EditAnywhere, Category = "MovingPlatform", Meta = (MakeEditWidget = true))
		TArray<FVector> TargetPoints;

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
};

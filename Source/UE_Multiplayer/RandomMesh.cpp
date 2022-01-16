// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMesh.h"

// Sets default values
ARandomMesh::ARandomMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RandomMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RandomMesh"));
}

// Called when the game starts or when spawned
void ARandomMesh::BeginPlay()
{
	Super::BeginPlay();

	/*if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}*/
	
}

// Called every frame
void ARandomMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetPoints[0]);
	FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
	Location += 20 * DeltaTime * Direction;
	SetActorLocation(Location);
}


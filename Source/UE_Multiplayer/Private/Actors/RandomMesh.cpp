// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RandomMesh.h"

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

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetPoints[0]);
	
}

// Called every frame
void ARandomMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();	
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += 100 * DeltaTime * Direction;
		SetActorLocation(Location);
		
	}
}



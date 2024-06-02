// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBars/RingedPowerBar.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"


// Sets default values
ARingedPowerBar::ARingedPowerBar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh;
		ConstructorHelpers::FObjectFinder<UMaterial> BattSourceMat;
		ConstructorHelpers::FObjectFinder<UMaterial> BattOffMat;

		FConstructorStatics()
			: CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"))
			, BattSourceMat(TEXT("/Game/Materials/Indicator/MI_BatterySource.MI_BatterySource"))
		    , BattOffMat(TEXT("/Game/Materials/Indicator/MM_PowerOff.MM_PowerOff"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	MeshGroup = CreateDefaultSubobject<USceneComponent>("Mesh Group");
	SpacerMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Spacer Meshes");
	RingMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Ring Meshes");

	SpacerMeshes->SetStaticMesh(ConstructorStatics.CylinderMesh.Object);
	SpacerMeshes->SetMaterial(0, ConstructorStatics.BattOffMat.Object);
	RingMeshes->SetStaticMesh(ConstructorStatics.CylinderMesh.Object);
	RingMeshes->SetMaterial(0, ConstructorStatics.BattSourceMat.Object);

	SpacerMeshes->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RingMeshes->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RingMeshes->SetRelativeScale3D(FVector(0.9f, 0.9f, 1.0f));

	RootComponent = Root;
	MeshGroup->SetupAttachment(RootComponent);
	SpacerMeshes->SetupAttachment(MeshGroup);
	RingMeshes->SetupAttachment(MeshGroup);
}

void ARingedPowerBar::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GenerateBars();
}

// Called when the game starts or when spawned
void ARingedPowerBar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARingedPowerBar::GenerateBars()
{
	SpacerMeshes->ClearInstances();
	RingMeshes->ClearInstances();

	constexpr float SpacerHeight = 0.05f;
	constexpr float RingHeight = 0.3f;
	const FVector SpacerScale = FVector(1, 1, SpacerHeight);
	const FVector RingScale = FVector(1, 1, RingHeight);

	for (int i = 0; i < RingCount; ++i)
	{
		const FVector SpacerLocation = FVector(0, 0, RingHeight * 100 * i);
		const FVector RingLocation = FVector(0, 0, ((RingHeight * 100)/2) + (RingHeight * 100 * i));
		SpacerMeshes->AddInstance(FTransform(FRotator::ZeroRotator, SpacerLocation, SpacerScale));
		RingMeshes->AddInstance(FTransform(FRotator::ZeroRotator, RingLocation, RingScale));
	}

	// Final spacer for the top
	SpacerMeshes->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0, 0, ((RingHeight * 100) * (RingCount - 1)) + (RingHeight * 100)), SpacerScale));
}

// Called every frame
void ARingedPowerBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractIndicator.h"


// Sets default values for this component's properties
UInteractIndicator::UInteractIndicator()
{
	PrimaryComponentTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh;
		ConstructorHelpers::FObjectFinder<UMaterialInterface> Mat;

		FConstructorStatics()
			: Mesh(TEXT("/Game/Meshes/CylinderCapless.CylinderCapless"))
			, Mat(TEXT("/Game/Materials/Indicator/MM_IndicatorUX.MM_IndicatorUX"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	CacheMesh = ConstructorStatics.Mesh.Object;
	CacheMat = ConstructorStatics.Mat.Object;
	SetRelativeScale3D(FVector::Zero());
}


// Called when the game starts
void UInteractIndicator::BeginPlay()
{
	Super::BeginPlay();
	//SetComponentTickEnabled(false);
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules( EAttachmentRule::KeepRelative, true );
	FVector ActorOrigin;
	FVector ActorBounds;
	GetOwner()->GetActorBounds(false, ActorOrigin, ActorBounds);
	IndicatorScale = FVector(FVector2D((FMath::Max(ActorBounds.X, ActorBounds.Y) * 2) / 100 + 0.8f), 0.4f);
	MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	MeshComponent->SetMaterial(0, CacheMat);
	MeshComponent->SetWorldScale3D(IndicatorScale);
	MeshComponent->SetStaticMesh(CacheMesh);
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetCastShadow(false);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->RegisterComponent();
	MeshComponent->AttachToComponent(this, AttachRules);
	SetRelativeLocation(FVector(0, 0, ActorOrigin.Z) - FVector(0, 0, GetOwner()->GetActorLocation().Z));
}


// Called every frame
void UInteractIndicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsActivated)
	{
		Alpha += DeltaTime / Speed;
		
	}
	else
	{
		Alpha -= DeltaTime / Speed;
	}
	Alpha = FMath::Clamp(Alpha, 0, 1);
	SetRelativeScale3D(FMath::Lerp(FVector::Zero(), FVector::One(), Alpha));
}

void UInteractIndicator::ActivateIndicator(bool bActivate)
{
	bIsActivated = bActivate;
	//SetComponentTickEnabled(bActivate);
}


﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ButtonComponent.h"


// Sets default values for this component's properties
UButtonComponent::UButtonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetWorldScale3D(FVector(0.3f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/InvertedChamferCube.InvertedChamferCube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ButtonMat(TEXT("/Game/Materials/Buttons/MM_ButtonBase.MM_ButtonBase"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ShellMat(TEXT("/Game/Materials/Buttons/MM_ButtonShell.MM_ButtonShell"));
	CubeMesh = Cube.Object;
	check(CubeMesh != nullptr);
	CylinderMesh = Cylinder.Object;
	check(CylinderMesh != nullptr);
	check(ButtonMat.Object != nullptr);
	check(ShellMat.Object != nullptr);

	CollisionComponent = CreateDefaultSubobject<UStaticMeshComponent>("Collision Component");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCastShadow(false);
	CollisionComponent->SetComponentTickEnabled(false);
	CollisionComponent->SetMaterial(0, ButtonMat.Object);
	CollisionComponent->SetupAttachment(this);

	ShellComponent = CreateDefaultSubobject<UStaticMeshComponent>("Shell Component");
	ShellComponent->SetCollisionProfileName("NoCollision");
	ShellComponent->SetCastShadow(false);
	ShellComponent->SetComponentTickEnabled(false);
	ShellComponent->SetRelativeScale3D(FVector(1.1f));
	ShellComponent->SetMaterial(0, ShellMat.Object);
	ShellComponent->SetupAttachment(CollisionComponent);

	IconComponent = CreateDefaultSubobject<UStaticMeshComponent>("Icon Component");
	IconComponent->SetCollisionProfileName("NoCollision");
	IconComponent->SetCastShadow(false);
	IconComponent->SetComponentTickEnabled(false);
	IconComponent->SetRelativeScale3D(FVector(0.9f));
	IconComponent->SetMaterial(0, ShellMat.Object);
	IconComponent->SetupAttachment(CollisionComponent);
}


// Called when the game starts
void UButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	switch (ButtonShape)
	{
		case (EButtonShape::Cube):
		{
			CollisionComponent->SetStaticMesh(CubeMesh);
			ShellComponent->SetStaticMesh(CubeMesh);
			break;
		}
		case (EButtonShape::Cylinder):
		{
			CollisionComponent->SetStaticMesh(CylinderMesh);
			ShellComponent->SetStaticMesh(CylinderMesh);
			break;
		}
	}
	IconComponent->SetStaticMesh(IconMesh);
	IconComponent->SetRelativeScale3D(IconScale);
}

// Called every frame
void UButtonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UButtonComponent::Enable(bool bEnabled)
{
	SetVisibility(bEnabled, true);

	if (bEnabled)
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UButtonComponent::OnMouseClicked_Implementation()
{
	ICursorInteractionInterface::OnMouseClicked_Implementation();
	OnButtonClicked.Broadcast();
}

void UButtonComponent::OnCursorEnter_Implementation()
{
	ICursorInteractionInterface::OnCursorEnter_Implementation();
	ShellComponent->SetRelativeScale3D(FVector(1.2f));
}

void UButtonComponent::OnCursorExit_Implementation()
{
	ICursorInteractionInterface::OnCursorExit_Implementation();
	ShellComponent->SetRelativeScale3D(FVector(1.1f));
}


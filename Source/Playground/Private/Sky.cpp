// Fill out your copyright notice in the Description page of Project Settings.


#include "Sky.h"

#include "Components/DirectionalLightComponent.h"
#include "Curves/CurveLinearColor.h"


// Sets default values
ASky::ASky()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	SkyBox = CreateDefaultSubobject<UStaticMeshComponent>("SkyBox Mesh");
	Sun = CreateDefaultSubobject<UDirectionalLightComponent>("Sun");
	Moon = CreateDefaultSubobject<UDirectionalLightComponent>("Moon");

	Sun->Intensity = 3.0;
	Sun->bUseTemperature = true;
	Sun->ForwardShadingPriority = 1;
	Sun->SetRelativeRotation(FRotator(-45.0, 0, 0));
	
	Moon->Intensity = 3.0;
	Moon->bUseTemperature = true;
	Moon->LightColor = FColor(136, 156, 232, 255);
	Moon->AtmosphereSunLightIndex = 1;
	Moon->SetRelativeRotation(FRotator(45.0, 180.0, 180.0));
	
	RootComponent = Root;
	SkyBox->SetupAttachment(RootComponent);
	Sun->SetupAttachment(RootComponent);
	Moon->SetupAttachment(RootComponent);

	Time = 12;
}

void ASky::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (SkyBox != nullptr && SkyBox->GetMaterial(0) != nullptr)
	{
		SkyMat = UMaterialInstanceDynamic::Create(SkyBox->GetMaterial(0)->GetMaterial(), this);
		SkyBox->SetMaterial(0, SkyMat);
	}

	//if (bToggleSkyRefresh || !bToggleSkyRefresh)
	//{
	//	bToggleSkyRefresh = false;
	//	UpdateSky();
	//}
}

// Called when the game starts or when spawned
void ASky::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITORONLY_DATA
	SetActorTickEnabled(bPlayInEditor);
#endif
}

// Called every frame
void ASky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Pitch = (Time / 24) * 360;
	Time += GetWorld()->DeltaTimeSeconds;
	if (Time >= 24) { Time = 0; }
	Sun->SetRelativeRotation(FRotator(Pitch, 0, 0));
	Moon->SetRelativeRotation(FRotator(Pitch - 180, 0, 0));
	UpdateSky_Implementation();
}

void ASky::UpdateSky_Implementation()
{
	const float SunHeight = GetSunHeight();
	
	SkyMat->SetVectorParameterValue("LightDirection", GetSunForward() * -1);
	if (HorizonCurve != nullptr) SkyMat->SetVectorParameterValue("HorizonColor", HorizonCurve->GetLinearColorValue(SunHeight));
	if (ZenithCurve != nullptr) SkyMat->SetVectorParameterValue("ZenithColor", ZenithCurve->GetLinearColorValue(SunHeight));
	if (CloudCurve != nullptr) SkyMat->SetScalarParameterValue("CloudStrength", CloudCurve->GetFloatValue(SunHeight));
}

FVector ASky::GetSunForward()
{
	return Sun->GetForwardVector();
}

float ASky::GetSunHeight() const
{
	return FMath::GetMappedRangeValueClamped(FVector2D(0.0f, -90.0f), FVector2D(0.0f, 1.0f), Sun->GetRelativeRotation().Pitch);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SolarPowerComponent.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USolarPowerComponent::USolarPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USolarPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	LightActor = UGameplayStatics::GetActorOfClass(this, ADirectionalLight::StaticClass()); // Getting global Directional Light
}

void USolarPowerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void USolarPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CastComponent != nullptr)
	{
		float Dot = FVector::DotProduct(CastComponent->GetForwardVector(), LightActor->GetActorForwardVector());
		float MinMaxDot = FVector::DotProduct(FVector::UpVector, FVector::UpVector.RotateAngleAxis(75, FVector::ForwardVector));
		//UE_LOG(LogTemp, Log, TEXT("Dot: %f, MinMax: %f"), Dot, MinMaxDot);

		// True if receiving sunlight
		if (Dot >= -1 && Dot <= -MinMaxDot)
		{
			OnSunlightReceivedDelegate.Broadcast(DeltaTime);
		}
	}
}


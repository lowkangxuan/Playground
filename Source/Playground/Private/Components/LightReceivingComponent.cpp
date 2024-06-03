// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LightReceivingComponent.h"
#include "Sky.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULightReceivingComponent::ULightReceivingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightReceivingComponent::BeginPlay()
{
	Super::BeginPlay();
	SkyActor = Cast<ASky>(UGameplayStatics::GetActorOfClass(this, ASky::StaticClass())); // Getting global Directional Light
	check(SkyActor);
}

void ULightReceivingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void ULightReceivingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (IsValid(CastComponent))
	{
		float Dot = FVector::DotProduct(CastComponent->GetForwardVector(), SkyActor->GetSunForward());
		float MinMaxDot = FVector::DotProduct(FVector::UpVector, FVector::UpVector.RotateAngleAxis(MaxSunAngle, FVector::ForwardVector));

		// True if receiving sunlight
		if (Dot >= -1 && Dot <= -MinMaxDot)
		{
			bIsReceivingSunlight = true;
			bWasReceivingSunlightLastFrame = true;
			OnSunlightReceivedDelegate.Broadcast(DeltaTime);
		}
		else
		{
			bIsReceivingSunlight = false;
		}

		// Call the delegate once when not receiving any Sunlight
		if (!bIsReceivingSunlight && bWasReceivingSunlightLastFrame)
		{
			bWasReceivingSunlightLastFrame = false;
			OnSunlightBlockedDelegate.Broadcast();
		}
	}
}


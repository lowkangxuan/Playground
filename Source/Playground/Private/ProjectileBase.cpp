// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Shield/ShieldInterface.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	SetRootComponent(ProjectileMesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->InitialSpeed = 2500;
	ProjectileMovementComponent->MaxSpeed = 2500;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = LifeSpan;
	OnActorHit.AddDynamic(this, &AProjectileBase::OnHit);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::FireTowardsDir(const FVector Dir)
{
	ProjectileMovementComponent->Velocity = Dir * ProjectileMovementComponent->InitialSpeed;
}

void AProjectileBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->ImplementsInterface(UShieldInterface::StaticClass()))
	{
		IShieldInterface::Execute_TakeDamge(Cast<UObject>(OtherActor), CalculateOutgoingDamage(), FDamageEvent(), GetInstigatorController(), this);
	}
	else
	{
		OtherActor->TakeDamage(CalculateOutgoingDamage(), FDamageEvent(), GetInstigatorController(), this);
	}

	Destroy(); //Destroy projectile upon hitting an object in the World
}

float AProjectileBase::CalculateOutgoingDamage_Implementation()
{
	bool CanCrit = (FMath::RandRange(0.0f, 1.0f) <= CritPercentage);
	return (CanCrit ? Damage * CritMultipler : Damage);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyShooter.h"
#include "ProjectileBase.h"

// Sets default values
ADummyShooter::ADummyShooter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileSpawnPoints.Init(FVector(100, 0, 100), 1);
}

// Called when the game starts or when spawned
void ADummyShooter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ADummyShooter::Fire, FireRate, true, 1);

	if (bShootBurst)
	{
		GetWorldTimerManager().SetTimer(BurstShootingTimerHandle, this, &ADummyShooter::BurstFire, BurstRate, true);
	}
}

void ADummyShooter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(ShootTimerHandle); //Clear shoot timer

	if (bShootBurst)
	{
		GetWorldTimerManager().ClearTimer(BurstShootingTimerHandle);
	}
}

// Called every frame
void ADummyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADummyShooter::Fire_Implementation()
{
	if (!Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("DummyShooter: No Projectile!"));
		return;
	}

	if (bShootBurst)
	{
		RemainingBurstShots = BurstShots;
		GetWorldTimerManager().UnPauseTimer(BurstShootingTimerHandle);
		return;
	}

	SpawnProjectile();
}

void ADummyShooter::BurstFire()
{
	if (--RemainingBurstShots < 0)
	{
		GetWorldTimerManager().PauseTimer(BurstShootingTimerHandle);
		return;
	}

	SpawnProjectile();
}

void ADummyShooter::SpawnProjectile_Implementation()
{
	AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile, GetActorLocation() + FTransform(GetActorRotation()).TransformVector(ProjectileSpawnPoints[0]), FRotator::ZeroRotator, FActorSpawnParameters());
	SpawnedProjectile->FireTowardsDir(GetActorForwardVector());
	OnProjectileSpawn();
}

void ADummyShooter::OnProjectileSpawn_Implementation()
{
}
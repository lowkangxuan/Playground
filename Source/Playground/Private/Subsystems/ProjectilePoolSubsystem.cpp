#include "Subsystems/ProjectilePoolSubsystem.h"
#include "ProjectileBase.h"

bool UProjectilePoolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UProjectilePoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	for (int i = 0; i < InitialPoolSize; i++)
	{
		CreateProjectile();
	}
}

void UProjectilePoolSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

AProjectileBase* UProjectilePoolSubsystem::RetrieveFromPool()
{
	if (ProjectilePool.Num() == 0)
	{
		CreateProjectile(); // Create new projectile if attempting to retrieve an empty pool
	}
	return ProjectilePool[0];
}

void UProjectilePoolSubsystem::ReturnToPool(AProjectileBase* ProjectileToReturn)
{
	ProjectilePool.Emplace(ProjectileToReturn);
}

void UProjectilePoolSubsystem::CreateProjectile()
{
	AProjectileBase* NewProjectile = GetWorld()->SpawnActor<AProjectileBase>(AProjectileBase::StaticClass(), FTransform::Identity);
	ProjectilePool.Emplace(NewProjectile);
}

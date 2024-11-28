// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyDemoProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AMyDemoProjectile::AMyDemoProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyDemoProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AMyDemoProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	//UE_LOG(LogTemp, Warning, TEXT("Before Destory Projectile Address: %p"), this);
	//AActor* OwnerActor = GetOwner();
	//if (OwnerActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Before Destory Projectile's Owner Address: %p"), OwnerActor);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Before Destory Projectile has no Owner"));
	//}

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	//UE_LOG(LogTemp, Warning, TEXT("After Destory Projectile Address: %p"), this);
	//OwnerActor = GetOwner();
	//if (OwnerActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("After Destory Projectile's Owner Address: %p"), OwnerActor);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("After Destory Projectile has no Owner"));
	//}
}

void AMyDemoProjectile::BeginPlay()
{
    Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Projectile Address: %p"), this);
	//AActor* OwnerActor = GetOwner();
	//if (OwnerActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Projectile's Owner Address: %p"), OwnerActor);
	//}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor/Cube.h"
#include "MyDemo/MyDemoProjectile.h"
#include "GameFramework/PlayerState.h"
#include "State/MyGameState.h"
#include "MyDemo/MyDemoCharacter.h"
#include "GameFramework/PlayerController.h"



// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true); 
	Mesh->OnComponentHit.AddDynamic(this, &ACube::OnHit); 
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (AMyDemoProjectile* Projectile = Cast<AMyDemoProjectile>(OtherActor))
    {
        if (AController* InstigatorController = Projectile->GetInstigatorController())
        {
            if (APlayerController* PlayerController = Cast<APlayerController>(InstigatorController))
            {
                AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>();
                 if (GameState)
                {
                    int ScoreToAdd = PointValue;
                    if (bIsImportantTarget)
                    {
                        ScoreToAdd *= 2;
                    }
                    GameState->AddScore(PlayerController, ScoreToAdd);
                }
            }
        }

        if (!bHitOnce)
        {
            bHitOnce = true;
            SetActorScale3D(GetActorScale3D() * ScaleOnHit);
        }
        else
        {
            Destroy();
        }
    }
}

void ACube::SetColor(FLinearColor NewColor)
{
    UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Red.MI_Solid_Red"));
    if (Material)
    {
        Mesh->SetMaterial(0, Material);
    }
}

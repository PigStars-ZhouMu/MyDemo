// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class MYDEMO_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SetColor(FLinearColor NewColor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	bool bHitOnce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	float ScaleOnHit = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	int32 PointValue = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	bool bIsImportantTarget = false;
};

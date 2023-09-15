// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_StateMachine.generated.h"


class UState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEMACHINE_API UAC_StateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_StateMachine();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UState> initialState;

	UPROPERTY(VisibleAnywhere)
	UState* currentState;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
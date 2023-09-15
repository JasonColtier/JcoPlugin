// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FTransitionDelegate,bool&,canTransition);


USTRUCT(BlueprintType)
struct FTransition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransitionDelegate transitionFunction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UState> nextState;
};

/**
 * 
 */
UCLASS(Blueprintable)
class STATEMACHINE_API UState : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta = (AutoCreateRefTerm = "function"))
	void AddTransition(FTransitionDelegate function,TSubclassOf<UState> nextState)
	{
		
	}

	UState()
	{
		UE_LOG(LogTemp, Log, TEXT("new state") );
	}

	~UState()
	{
		UE_LOG(LogTemp, Log, TEXT("delete state") );
	}

	UFUNCTION(BlueprintImplementableEvent)
	void Tick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnterState();

	UFUNCTION(BlueprintImplementableEvent)
	void OnExitState();

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeTransitions();
	
private:
	UPROPERTY()
	TArray<FTransition> transitionsArray;
};

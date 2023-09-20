// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

class UAC_StateMachine;
DECLARE_DYNAMIC_DELEGATE_TwoParams(FTransitionDelegate, TSubclassOf<UState>&, nextState, bool&, canTransition);


/**
 * 
 */
UCLASS(Blueprintable)
class STATEMACHINE_API UState : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UAC_StateMachine* StateMachineRef;

	UPROPERTY()
	FTransitionDelegate defaultTransitionDelegate;

	TArray<FTransitionDelegate*> transitionsArray;

	
	UState();


	~UState();
	
	UFUNCTION(BlueprintCallable,meta = (AutoCreateRefTerm = "function"))
	void AddTransition(FTransitionDelegate function);
	
	UFUNCTION(BlueprintImplementableEvent)
	void Tick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnterState();

	UFUNCTION(BlueprintImplementableEvent)
	void OnExitState();

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeTransitions();

	UFUNCTION(BlueprintImplementableEvent)
	void DefaultTransition(TSubclassOf<UState>& nextState,bool& canTransition);
	

};

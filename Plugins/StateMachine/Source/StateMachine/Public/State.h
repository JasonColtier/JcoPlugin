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

	/**
	 * @brief La référence à la state machine
	 */
	UPROPERTY(BlueprintReadOnly)
	UAC_StateMachine* StateMachineRef;

	/**
	 * @brief the default transition of this state, can be configured in BP
	 */
	UPROPERTY()
	FTransitionDelegate defaultTransitionDelegate;

	/**
	 * @brief the transitions of this state to other states
	 */
	TArray<FTransitionDelegate> transitionsArray;

	
	UState();
	
	~UState();
	
	/**
	 * @brief Adds a transition to the transition array
	 * @param function 
	 */
	UFUNCTION(BlueprintCallable,meta = (AutoCreateRefTerm = "function"))
	void AddTransition(const FTransitionDelegate& function);
	
	/**
	 * @brief tick recieved from the state machine
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void Tick();

	/**
	 * @brief When this state is initialised
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnEnterState();

	/**
	 * @brief When this state is exited
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnExitState();

	/**
	 * @brief the default transition of this state
	 * @param nextState 
	 * @param canTransition 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void DefaultTransition(TSubclassOf<UState>& nextState,bool& canTransition);
	
	/**
	 * @brief 
	 * @param transitions Gets the next states from the current state
	 */
	UFUNCTION(BlueprintCallable)
	void GetTransitions(TArray<TSubclassOf<UState>>& transitions);
};

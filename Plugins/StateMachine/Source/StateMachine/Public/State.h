// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

class UAC_StateMachine;
DECLARE_DYNAMIC_DELEGATE_TwoParams(FTransitionDelegate, TSoftClassPtr<AState>&, nextState, bool&, canTransition);


/**
 * 
 */
UCLASS()
class STATEMACHINE_API AState : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginDestroy() override;

protected:
	virtual void BeginPlay() override;

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

	/**
	 * @brief Adds a transition to the transition array
	 * @param function 
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "function"))
	void AddTransition(const FTransitionDelegate& function);

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
	void DefaultTransition(TSoftClassPtr<AState>& nextState, bool& canTransition);

	/**
	 * @brief 
	 * @param transitions Gets the next states from the current state
	 */
	UFUNCTION(BlueprintCallable)
	void GetTransitions(TArray<TSoftClassPtr<AState>>& transitions);
};

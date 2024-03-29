// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_StateMachine.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(StateMachine, Log, All);


class AState;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeState,AState*,currentState);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class STATEMACHINE_API UAC_StateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_StateMachine();

	/**
	 * @brief the initial state of the state machine
	 */
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AState> initialState;

	/**
	 * @brief the current state of the state machine
	 */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AState> currentState;

	/**
	 * @brief draws debug states and transition on screen
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool showDebug = false;

	/**
	 * @brief called when a state is changed, idealy this sould be used sparingly to keep the states autonomous
	 */
	UPROPERTY(BlueprintAssignable)
	FOnChangeState OnChangeStateDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief 
	 * @param newState Changes the current state of the state machine to the new state. The new state is instantiated
	 */
	void ChangeState(TSoftClassPtr<AState> newState);

	/**
	 * @brief Force the state machine to switch to the desired state, no transition check is done
	 * @param newState 
	 */
	UFUNCTION(BlueprintCallable)
	void ForceChangeState(TSoftClassPtr<AState> newState);

private:
	/**
	 * @brief Checks the transition of the current state to see if it can transition to another state
	 */
	UFUNCTION()
	void CheckTransitions();
};

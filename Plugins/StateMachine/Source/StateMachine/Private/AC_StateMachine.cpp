// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_StateMachine.h"

#include "State.h"

DEFINE_LOG_CATEGORY(StateMachine);

// Sets default values for this component's properties
UAC_StateMachine::UAC_StateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAC_StateMachine::BeginPlay()
{
	Super::BeginPlay();

	if (initialState != nullptr)
	{
		ChangeState(initialState);
	}
	else
	{
		UE_LOG(StateMachine, Error, TEXT("no initial state"));
	}
}


// Called every frame
void UAC_StateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!currentState)
		return;


	CheckTransitions();
	currentState->Tick();
}

void UAC_StateMachine::ChangeState(TSoftClassPtr<UState> newState)
{
	if (newState.IsNull())
	{
		UE_LOG(StateMachine, Error, TEXT("invalid state passed as parameter"));
		return;
	}

	if (currentState != nullptr)
	{
		currentState->OnExitState();
		currentState->MarkAsGarbage();
	}
	
	currentState = NewObject<UState>(this, newState.LoadSynchronous());
	currentState->StateMachineRef = this;
	currentState->OnEnterState();
	OnChangeStateDelegate.Broadcast(currentState);
}

void UAC_StateMachine::ForceChangeState(TSoftClassPtr<UState> newState)
{
	if (newState)
	{
		UE_LOG(StateMachine, Log, TEXT("forcing state change to %s"), *newState->GetClass()->GetName());
		ChangeState(newState);
	}else
	{
		UE_LOG(StateMachine, Log, TEXT("bad state provided"));
	}
}

void UAC_StateMachine::CheckTransitions()
{
	for (const auto& transition : currentState->transitionsArray)
	{
		bool canTransition;
		TSoftClassPtr<UState> nextState;
		transition.Execute(nextState, canTransition);
		if (canTransition)
		{
			ChangeState(nextState.Get());
			return;
		}
	}

	UE_LOG(StateMachine, Log, TEXT("no transition found "));
}

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
void UAC_StateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!currentState)
		return;


	CheckTransitions();
}

void UAC_StateMachine::ChangeState(TSoftClassPtr<AState> newState)
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

	currentState = GetWorld()->SpawnActor<AState>(newState.LoadSynchronous(),GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	currentState->StateMachineRef = this;
	OnChangeStateDelegate.Broadcast(currentState);
	currentState->OnEnterState();
}

void UAC_StateMachine::ForceChangeState(TSoftClassPtr<AState> newState)
{
	if (newState.IsNull())
	{
		UE_LOG(StateMachine, Error, TEXT("invalid state passed as parameter when force loading"));
		return;
	}
	
	UE_LOG(StateMachine, Log, TEXT("forcing state change to %s"), *newState->GetClass()->GetName());
	ChangeState(newState);
}

void UAC_StateMachine::CheckTransitions()
{
	if(!IsValid(currentState))
	{
		UE_LOG(StateMachine, Error, TEXT("invalid current state !"));
		return;
	}

	if(currentState->transitionsArray.IsEmpty())
	{
		UE_LOG(StateMachine, Error, TEXT("no transition found !"));
		return;
	}
	
	for (const auto& transition : currentState->transitionsArray)
	{
		bool canTransition;
		TSoftClassPtr<AState> nextState;
		transition.Execute(nextState, canTransition);
		if (canTransition)
		{
			ChangeState(nextState.Get());
			return;
		}
	}
	UE_LOG(StateMachine, Log, TEXT("cannot transition from current state"));
}

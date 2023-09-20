// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_StateMachine.h"

#include "State.h"

// Sets default values for this component's properties
UAC_StateMachine::UAC_StateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickInterval(0.5);
	// ...
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
		UE_LOG(LogTemp, Error, TEXT("no initial state"));
	}
}


// Called every frame
void UAC_StateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckTransitions();
	currentState->Tick();
}

void UAC_StateMachine::ChangeState(TSubclassOf<UState> newState)
{
	if (newState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("invalid state passed as parameter"));
		return;
	}
	
	if (currentState != nullptr)
	{
		currentState->OnExitState();
		currentState->MarkAsGarbage();

	}

	currentState = NewObject<UState>(this, newState);
	currentState->StateMachineRef = this;
	currentState->OnEnterState();
}

void UAC_StateMachine::CheckTransitions()
{
	for (const auto& transition : currentState->transitionsArray)
	{
		bool canTransition;
		TSubclassOf<UState> nextState;
		transition->Execute(nextState, canTransition);
		if (canTransition)
		{
			UE_LOG(LogTemp, Log, TEXT("transition found !"));
			ChangeState(nextState);
			return;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("no transition found "));
}

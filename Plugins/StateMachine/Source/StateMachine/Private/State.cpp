// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

#include "AC_StateMachine.h"

UState::UState()
{
	UE_LOG(StateMachine, Log, TEXT("state created %s"), *GetName());
	defaultTransitionDelegate.BindUFunction(this, "DefaultTransition");
	transitionsArray.AddUnique(defaultTransitionDelegate);
}

void UState::AddTransition(const FTransitionDelegate& function)
{
	transitionsArray.AddUnique(function);
	UE_LOG(StateMachine, Log, TEXT("added transition %s"), *function.GetFunctionName().ToString());
}

void UState::GetTransitions(TArray<TSoftClassPtr<UState>>& transitions)
{
	for (const auto& transition : transitionsArray)
	{
		if (transition.IsBound())
		{
			TSoftClassPtr<UState> nextState;
			bool tmp;
			transition.Execute(nextState, tmp);
			transitions.Add(nextState);
		}
		else
		{
			UE_LOG(StateMachine, Error, TEXT("transition not bound"));
		}
	}
}

UState::~UState()
{
	// UE_LOG(StateMachine, Warning, TEXT("delete state %s"), *GetName());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

UState::UState()
{
	UE_LOG(LogTemp, Warning, TEXT("state created %s"),*GetName());
	defaultTransitionDelegate.BindUFunction(this,"DefaultTransition");
	transitionsArray.AddUnique(&defaultTransitionDelegate);
	UE_LOG(LogTemp, Log, TEXT("num transitions %s %i"),*GetName(),transitionsArray.Num());

	InitializeTransitions();
	
}

void UState::AddTransition(FTransitionDelegate function)
{
	transitionsArray.AddUnique(&function);
	UE_LOG(LogTemp, Log, TEXT("added transition %s"),*function.GetFunctionName().ToString());
}

UState::~UState()
{
	UE_LOG(LogTemp, Warning, TEXT("delete state %s"),*GetName() );
}

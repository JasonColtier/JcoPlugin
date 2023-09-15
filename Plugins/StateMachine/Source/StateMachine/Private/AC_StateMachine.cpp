// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_StateMachine.h"

#include "State.h"

// Sets default values for this component's properties
UAC_StateMachine::UAC_StateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_StateMachine::BeginPlay()
{
	Super::BeginPlay();

	if(initialState != nullptr)
	{
		currentState = NewObject<UState>(this,initialState);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("no initial state") );
	}
}


// Called every frame
void UAC_StateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// currentState->
}


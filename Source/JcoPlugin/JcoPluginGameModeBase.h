// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JCOCheatManager.h"
#include "GameFramework/GameModeBase.h"
#include "JcoGameInstanceSubsystem.h"
#include "JcoPluginGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class JCOPLUGIN_API AJcoPluginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	DeclareJcoDebug;
	
};

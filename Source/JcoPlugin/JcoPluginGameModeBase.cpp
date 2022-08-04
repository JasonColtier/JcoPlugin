// Copyright Epic Games, Inc. All Rights Reserved.


#include "JcoPluginGameModeBase.h"

#include "JCOCheatManager.h"
#include "LogTool.h"

DEFINE_LOG_CATEGORY(FS_Log);

void AJcoPluginGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetJcoGameInstance;
	TRACE("simple trace");
	TRACE_WARNING("trace warning");
	TRACE_ERROR("trace error");
	TRACE_SCREEN(10, "SCREEN TRACE");

}

void AJcoPluginGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Debug
	{
		TRACE_ERROR("Ticking log : debug ");
	}

}

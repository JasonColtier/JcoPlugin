// Copyright Epic Games, Inc. All Rights Reserved.


#include "JcoPluginGameModeBase.h"

#include "../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"

DEFINE_LOG_CATEGORY(FS_Log);

void AJcoPluginGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TRACE("simple trace");
	TRACE_WARNING("trace warning");
	TRACE_ERROR("trace error");
	TRACE_SCREEN(10,"SCREEN TRACE");
}

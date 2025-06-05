// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Modules/ModuleManager.h"


class FYxEditorToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:
	void RegisterCustomizations();
	bool bRegistered = false;
};

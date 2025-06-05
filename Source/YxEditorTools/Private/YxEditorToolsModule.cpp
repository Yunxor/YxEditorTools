// Copyright Epic Games, Inc. All Rights Reserved.

#include "YxEditorToolsModule.h"
#include "YxEditorTypes.h"
#include "InlineGroupCustomization.h"

#define LOCTEXT_NAMESPACE "FYxEditorToolsModule"


void FYxEditorToolsModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FYxEditorToolsModule::RegisterCustomizations);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("ReloadInlineGroupCustomizer"),
		TEXT("Reloads the InlineGroup property customizer"),
		FConsoleCommandDelegate::CreateRaw(this, &FYxEditorToolsModule::RegisterCustomizations),
		ECVF_Default
	);
}

void FYxEditorToolsModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor") && bRegistered)
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(YxEditorTools::MD_InlineGroupStruct);
		bRegistered = false;
	}
}

void FYxEditorToolsModule::RegisterCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FModuleManager::Get().LoadModule("PropertyEditor");
	}
    
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
	if (bRegistered)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(YxEditorTools::MD_InlineGroupStruct);
	}

	PropertyModule.RegisterCustomPropertyTypeLayout(
		YxEditorTools::MD_InlineGroupStruct,
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FInlineGroupCustomization::MakeInstance)
	);

	// TODO : this can't work for the structure declared in the code, need to find greater API.
	// PropertyModule.RegisterCustomPropertyTypeLayout(
	// 	FStructProperty::StaticClass()->GetFName(),
	// 	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FInlineGroupCustomization::MakeInstance)
	// 	, MakeShared<FInlineGroupPropertyTypeIdentifier>()
	// );
    
	PropertyModule.NotifyCustomizationModuleChanged();
	bRegistered = true;
    
	UE_LOG(LogTemp, Log, TEXT("InlineGroup customizer successfully registered!"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYxEditorToolsModule, YxEditorTools)
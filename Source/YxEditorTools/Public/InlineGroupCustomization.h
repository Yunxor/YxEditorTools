#pragma once
#include "IPropertyTypeCustomization.h"
#include "YxEditorTypes.h"

class FInlineGroupPropertyTypeIdentifier : public IPropertyTypeIdentifier
{
public:
	FInlineGroupPropertyTypeIdentifier() = default;

	virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override
	{
		return PropertyHandle.HasMetaData(YxEditorTools::MD_InlineGroupStruct);
	}
};


class FInlineGroupCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	virtual bool ShouldInlineKey() const override { return true; }

	TMap<FString, TArray<TSharedRef<IPropertyHandle>>> GroupedProperties;
	
};

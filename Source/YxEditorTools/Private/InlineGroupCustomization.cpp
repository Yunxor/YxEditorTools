#include "InlineGroupCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#include "PropertyHandle.h"


#define LOCTEXT_NAMESPACE "InlineGroupCustomization"


TSharedRef<IPropertyTypeCustomization> FInlineGroupCustomization::MakeInstance()
{
	return MakeShareable(new FInlineGroupCustomization);
}

void FInlineGroupCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}


TSharedRef<SWidget> CreateInlineGroupWidget(TArray<TSharedRef<IPropertyHandle>>& Properties)
{
	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);
	for (auto& PropertyHandle : Properties)
	{
		FText PropertyDisplayName = PropertyHandle->GetPropertyDisplayName();
		HorizontalBox->AddSlot()
		.Padding(4.f, 0.f)
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 0.f, 0.f, 2.f)
			[
				SNew(STextBlock)
				.Text(PropertyDisplayName)
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				PropertyHandle->CreatePropertyValueWidgetWithCustomization(nullptr)
			]
		];
	}
	TSharedRef<SBorder> Border = SNew(SBorder).Padding(1.f)
		[
			HorizontalBox
		];
	return Border;
}

void FInlineGroupCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	GroupedProperties.Empty();

	uint32 NumChildren;
	FPropertyAccess::Result Result = PropertyHandle->GetNumChildren(NumChildren);
	if (Result == FPropertyAccess::Fail)
	{
		return;
	}
	
	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		TSharedRef<IPropertyHandle> Handle = PropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();
		FString GroupName = Handle->HasMetaData("Category") ? Handle->GetMetaData("Category") : TEXT("Default");
		TArray<TSharedRef<IPropertyHandle>>& Properties = GroupedProperties.FindOrAdd(GroupName);
		Properties.Emplace(Handle);
	}
	
	auto AddGroupPropertiesRow = [&ChildBuilder](const FString& GroupStr, TArray<TSharedRef<IPropertyHandle>>& Properties)
	{
		FText GroupText = FText::FromString(GroupStr);
		ChildBuilder.AddCustomRow(GroupText)
		.NameContent()
		[
			SNew(STextBlock)
			.Text(GroupText)
		]
		.ValueContent()
		[
			CreateInlineGroupWidget(Properties)
		]
		.ShouldAutoExpand(true);;
	};

	for (auto& Pair : GroupedProperties)
	{
		AddGroupPropertiesRow(Pair.Key, Pair.Value);
	}
}

#undef LOCTEXT_NAMESPACE

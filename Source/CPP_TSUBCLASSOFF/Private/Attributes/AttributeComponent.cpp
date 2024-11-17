#include "Attributes/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UAttributeComponent::HasAttribute(TSubclassOf<UAttribute> AttributeType) const
{
	return Attributes.Contains(AttributeType);
}

void UAttributeComponent::ModifyAttribute(TSubclassOf<UAttribute> AttributeType, float DeltaValue)
{
	if (UAttribute** FoundAttribute = Attributes.Find(AttributeType))
	{
		(*FoundAttribute)->SetValue((*FoundAttribute)->GetValue() + DeltaValue);
	}
}

UAttribute* UAttributeComponent::GetAttribute(TSubclassOf<UAttribute> AttributeType) const
{
	if (UAttribute* const* FoundAttribute = Attributes.Find(AttributeType))
	{
		return *FoundAttribute;
	}
	return nullptr;
}

bool UAttributeComponent::AddAttribute(TSubclassOf<UAttribute> AttributeType, float InitialValue)
{
	if (!Attributes.Contains(AttributeType))
	{
		UAttribute* NewAttribute = NewObject<UAttribute>(this, AttributeType);
		if (NewAttribute)
		{
			NewAttribute->SetValue(InitialValue);
			Attributes.Add(AttributeType, NewAttribute);
			return true;
		}
	}
	return false;
}

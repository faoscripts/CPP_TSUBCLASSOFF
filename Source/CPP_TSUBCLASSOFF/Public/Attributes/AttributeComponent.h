#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

UCLASS(Blueprintable)
class CPP_TSUBCLASSOFF_API UAttribute : public UObject
{
	GENERATED_BODY()

public:
	UAttribute() : Value(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float Value;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetValue() const { return Value; }

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetValue(float NewValue) { Value = NewValue; }
};

template <typename T>
class TMyAttribute
{
public:
	TMyAttribute(T InitialValue) : Value(InitialValue) {}

	T GetValue() const { return Value; }
	void SetValue(T NewValue) { Value = NewValue; }

private:
	T Value;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_TSUBCLASSOFF_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool HasAttribute(TSubclassOf<UAttribute> AttributeType) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ModifyAttribute(TSubclassOf<UAttribute> AttributeType, float DeltaValue);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	UAttribute* GetAttribute(TSubclassOf<UAttribute> AttributeType) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool AddAttribute(TSubclassOf<UAttribute> AttributeType, float InitialValue);

private:
	UPROPERTY()
	TMap<TSubclassOf<UAttribute>, UAttribute*> Attributes;

	TMap<FName, TMyAttribute<float>> GenericAttributes;
};
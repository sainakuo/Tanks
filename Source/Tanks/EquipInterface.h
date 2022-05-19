// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemInfo.h"
#include "UObject/Interface.h"
#include "EquipInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UEquipInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKS_API IEquipInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void EquipItem(EEquipSlot Slot, FName ItemId) {};
	virtual void UnEquipItem(EEquipSlot Slot, FName ItemId) {};
};

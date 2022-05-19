// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"

#include "EquipInterface.h"

UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::Es_Cannon);
	EquipSlots.Add(1, EEquipSlot::Es_Turret);
	EquipSlots.Add(2, EEquipSlot::Es_Body);
	EquipSlots.Add(3, EEquipSlot::Es_Tracks);
	
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	EEquipSlot* EquipSlotPtr = EquipSlots.Find(SlotIndex);
	if (InItem.Type == EItemType::It_Equip && EquipSlotPtr && *EquipSlotPtr == InItem.EquipSlot)
	{
		return 1;
	}
	return 0;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}

	IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner);
	if (EquipInterface)
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnEquipItem(EquipSlot, ItemInfo->Id);
		}

		Super::SetItem(SlotIndex, Item);
		EquipInterface->EquipItem(EquipSlot, Item.Id);
	}
}

void UEquipInventoryComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::ClearItem(SlotIndex);
		return;
	}

	IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner);
	if (EquipInterface)
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnEquipItem(EquipSlot, ItemInfo->Id);
		}

		Super::ClearItem(SlotIndex);
	}
}

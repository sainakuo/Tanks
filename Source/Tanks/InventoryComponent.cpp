// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

void UInventoryComponent::Init()
{
	if (SlotData)
	{
		TArray<FName> SlotDataRows = SlotData->GetRowNames();
		
		Items.Add(-1, *SlotData->FindRow<FInventorySlotInfo>(SlotDataRows[0], ""));
		
		for (int32 i = 0; i < SlotDataRows.Num()-1; i++)
		{
			Items.Add(i, *SlotData->FindRow<FInventorySlotInfo>(SlotDataRows[i+1], ""));
		}
	}
}

void UInventoryComponent::SetItem(int32 SlotIndex, FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

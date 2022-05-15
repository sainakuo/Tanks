// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemInfo.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	TMap<int32, FInventorySlotInfo> Items;

	UPROPERTY(EditAnywhere)
	UDataTable* SlotData;
	
public:

	void Init();
	
	const FInventorySlotInfo* GetItem(int32 SlotIndex) const{ return Items.Find(SlotIndex);}

	virtual void SetItem(int32 SlotIndex, FInventorySlotInfo& Item);

	virtual void ClearItem(int32 SlotIndex);

	const TMap<int32, FInventorySlotInfo>& GetItems() const {return Items;}

	int32 GetItemsNum() const { return Items.Num(); }

};

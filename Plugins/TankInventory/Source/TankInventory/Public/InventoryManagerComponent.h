// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "InventoryWidget.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryCellWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKINVENTORY_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	void InitEquip(UInventoryComponent* InInventoryComponent);

	const FInventoryItemInfo* GetItemData(const FName& InID) const;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	UInventoryWidget* EquipWidget;
	
protected:

	UPROPERTY()
	UInventoryComponent* LocalInventoryComponent;
	
	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> EquipWidgetClass;


	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
};

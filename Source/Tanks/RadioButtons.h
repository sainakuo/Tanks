// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRadioButtons.h"
#include "Components/Widget.h"
#include "RadioButtons.generated.h"

class SRadioButtons;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioButtonChangedEvent, int32, NewSelectedButton);

UCLASS()
class TANKS_API URadioButtons : public UWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "RadioButtons|Event")
	FOnRadioButtonChangedEvent OnRadioButtonChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 Count = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 CurrentIndex = 0;
	
	UFUNCTION(BlueprintCallable)
	void ChangeCount(int32 NewCount);

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;


protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<SRadioButtons> RadioButtons;
	void OnRadioButtonChangedFunc(int32 NewSelectedButton);

};

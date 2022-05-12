#include "MyCoreStyle.h"

#include "Slate/SlateGameResources.h"


TSharedPtr<ISlateStyle> FMyCoreStyle::StylePtr;

TSharedPtr<ISlateStyle> CreateStyle()
{
	FString ScopeToDirectory("/Game/UI");
	TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("MyCoreStyle"), ScopeToDirectory, ScopeToDirectory);
	
	return Style;
}

void FMyCoreStyle::Initialize()
{
	Shutdown();

	StylePtr = CreateStyle();

	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
	

}

void FMyCoreStyle::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}

}

const ISlateStyle& FMyCoreStyle::Get()
{
	if (!StylePtr.IsValid())
		Initialize();

	return *StylePtr;
}

#pragma once

#include "Slate.h"

class FMyCoreStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get();

private:
	static TSharedPtr<ISlateStyle> StylePtr;
};

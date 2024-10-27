// Copyright HungryHusky Games 2024

#include "Libraries/NGameFunctionLibrary.h"

UNGameFunctionLibrary::UNGameFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FBlueprintSupport::RegisterBlueprintWarning(
		FBlueprintWarningDeclaration(
			FName("RandomAccessToEmptyArrayWarning"),
			FText::FromString("Random access to empty array")
		)
	);
}

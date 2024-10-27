// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/NLevelManager.h"
#include "Core/AssetManager/NLevelPrimaryAsset.h"

#include "Engine.h"

ANLevelManager::ANLevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

ANLevelManager* ANLevelManager::GetLevelManager(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
		return nullptr;
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		for (TActorIterator<ANLevelManager> ItActor = TActorIterator<ANLevelManager>(World, ANLevelManager::StaticClass()); ItActor; ++ItActor)
			return *ItActor;
	}
	return nullptr;
}

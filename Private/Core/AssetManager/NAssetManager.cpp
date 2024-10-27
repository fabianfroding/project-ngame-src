// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Core/AssetManager/NAssetManager.h"

#include "Kismet/KismetSystemLibrary.h"

UNAssetManager* UNAssetManager::GetAssetManager()
{
	UNAssetManager* AssetManager = Cast<UNAssetManager>(GEngine->AssetManager);

	if (!ensure(AssetManager))
		return nullptr;

	return AssetManager;
}

UObject* UNAssetManager::LoadObjectFromSoftObjectPtr(TSoftObjectPtr<UObject> SoftObjectPtr)
{
	if (!UKismetSystemLibrary::IsValidSoftObjectReference(SoftObjectPtr))
		return nullptr;

	UObject* Object = SoftObjectPtr.Get();
	if (Object)
	{
		return Object;
	}

	Object = SoftObjectPtr.LoadSynchronous();
	if (Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNAssetManager::LoadObjectFromSoftObjectPtr: The object %s was synchronously."), *SoftObjectPtr.ToSoftObjectPath().ToString());
		return Object;
	}

	return nullptr;
}

UClass* UNAssetManager::LoadClassFromSoftClassPtr(TSoftClassPtr<UObject> SoftClassPtr)
{
	if (!UKismetSystemLibrary::IsValidSoftClassReference(SoftClassPtr))
		return nullptr;

	UClass* Class = SoftClassPtr.Get();
	if (Class)
	{
		return Class;
	}

	Class = SoftClassPtr.LoadSynchronous();
	if (Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNAssetManager::LoadClassFromSoftClassPtr: The class %s was loaded synchronously."), *SoftClassPtr.ToSoftObjectPath().ToString());
		return Class;
	}

	return nullptr;
}

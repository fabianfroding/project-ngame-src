// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

// Includes in alphabetic order.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NCodingStandard.generated.h" // Generated include below other includes and above forward declarations.

// Class forward declarations here.
class AActor;

UCLASS()
class NGAME_API ANCodingStandard : public AActor
{
	GENERATED_BODY()
	
	// Private properties first.
private:
	bool PrivateProperty = false;

	// Protected properties second.
protected:
	bool ProtectedProperty = false;

	// Public properties third.
public:
	bool PublicProperty = false;

	// Public functions fourth;
public:
	void PublicFunction() {};
	ANCodingStandard();

	// Protected functions fifth.
protected:
	void ProtectedFunction() {};
	virtual void BeginPlay() override;

	// Private functions last.
private:
	void PrivateFunction() {};
};

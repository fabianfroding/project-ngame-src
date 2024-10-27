// Copyright HungryHusky Games 2024

#include "Weapons/NWeapon.h"

void ANWeapon::SetCrosshair(UNCrosshair* InCrossHair)
{
	Crosshair = InCrossHair;
	Crosshair->OwningWeapon = this;
}

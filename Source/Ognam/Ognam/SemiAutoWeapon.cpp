// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "SemiAutoWeapon.h"
#include "Engine/World.h"
#include "WeaponActionModifier.h"

USemiAutoWeapon::USemiAutoWeapon()
{
}


void USemiAutoWeapon::BasicPressed()
{
	if (!CanBasic())
	{
		if (!bInfiniteAmmo && Ammo == 0)
		{
			ReloadPressed();
		}
		return;
	}
	ServerBasicPressed();
}

void USemiAutoWeapon::ServerBasicPressed_Implementation()
{
	if (!CanBasic())
	{
		return;
	}

	WeaponAction->NetExecuteAciton();
}

bool USemiAutoWeapon::CanBasic()
{
	return Super::CanBasic() && !WeaponAction->IsRunning();
}

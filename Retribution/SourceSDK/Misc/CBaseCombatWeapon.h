#pragma once
#include "..\Utils\Utils.h"

class CBaseCombatWeapon
{
public:
	inline int GetWeaponID();
	inline int GetBulletsInClip();
};

inline int CBaseCombatWeapon::GetWeaponID()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_iItemDefinitionIndex);
}

inline int CBaseCombatWeapon::GetBulletsInClip()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_iClip1);
}
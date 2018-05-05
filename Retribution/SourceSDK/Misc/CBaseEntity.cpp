#include "CBaseEntity.h"

int CBaseEntity::GetIndex()
{
	return gUtils.ReadAdress<int>(this, 0x64);
}

bool CBaseEntity::GetDormant()
{
	return gUtils.ReadAdress<bool>(this, Offsets::m_isDormant);
}

int CBaseEntity::GetTeamNumber()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_iTeamNum);
}

int CBaseEntity::GetHealth()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_iHealth);
}

int CBaseEntity::GetFlags()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_fFlags);
}

Vector CBaseEntity::GetEyePosition()
{
	return gUtils.ReadAdress<Vector>(this, Offsets::m_vecViewOffset) + this->GetAbsOrigin();
}

Vector& CBaseEntity::GetAbsOrigin()
{
	return gInterface.CallVirtualFunction<Vector&>(this, Indexes::BaseEntity::GetAbsOrigin);
}

Vector CBaseEntity::GetVelocity()
{
	return gUtils.ReadAdress<Vector>(this, Offsets::m_vecVelocity);
}

Vector CBaseEntity::GetBonePosition(int _boneId)
{
	DWORD boneAddress = gUtils.ReadAdress<DWORD>(this, Offsets::m_dwBoneMatrix);
	
	Vector vec;
	
	vec.x = gUtils.ReadAdress<float>(boneAddress, 0x30 * _boneId + 0x0C);
	vec.y = gUtils.ReadAdress<float>(boneAddress, 0x30 * _boneId + 0x1C);
	vec.z = gUtils.ReadAdress<float>(boneAddress, 0x30 * _boneId + 0x2C);
	
	return vec;
}

QAngle CBaseEntity::GetAimPunchAngle()
{
	return gUtils.ReadAdress<QAngle>(this, Offsets::m_aimPunchAngle);
}

int CBaseEntity::GetShotsFired()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_iShotsFired);
}

int CBaseEntity::GetTickBase()
{
	return gUtils.ReadAdress<int>(this, Offsets::m_nTickBase);
}

float CBaseEntity::GetNextAttack()
{
	return gUtils.ReadAdress<float>(this, Offsets::m_flNextAttack);
}

bool CBaseEntity::IsVisible(CBaseEntity* _localPlayer, int _boneId)
{
	if (!this || !_localPlayer)
		return false;

	trace_t trace = gUtils.TraceRay(_localPlayer->GetEyePosition(), this->GetBonePosition(_boneId), _localPlayer, MASK_VISIBLE);
	
	if (trace.m_pEnt != this || trace.fraction == 1.0)
		return false;
	
	return true;
}

bool CBaseEntity::IsValidTarget(CBaseEntity* _localPlayer, bool _targetTeammates, bool _targetPlayersInAir, bool _targetOnlyVisiblePlayers, int _visibleBoneId)
{
	if (!this || !_localPlayer)
		return false;

	if (this == _localPlayer)
		return false;

	int teamNum = this->GetTeamNumber();

	if (teamNum == 1) 
		return false;
	
	if (!_targetTeammates && teamNum == _localPlayer->GetTeamNumber())
		return false;

	if (!this->GetHealth())
		return false;

	if (this->GetDormant())
		return false;
	
	if (!_targetPlayersInAir && !(this->GetFlags() & FL_ONGROUND))
		return false;

	if (_targetOnlyVisiblePlayers && !this->IsVisible(_localPlayer, _visibleBoneId))
		return false;
	
	return true;
}

DWORD CBaseEntity::GetWeaponHandle()
{
	return gUtils.ReadAdress<DWORD>(this, Offsets::m_hActiveWeapon);
}

int CBaseEntity::GetWeapon()
{
	CBaseCombatWeapon* weaponEntity = (CBaseCombatWeapon*)(DWORD)gInterface.EntityList()->GetClientEntityFromHandle(this->GetWeaponHandle());
	return weaponEntity->GetWeaponID();
}

int CBaseEntity::GetWeapClip()
{
	CBaseCombatWeapon* weaponEntity = (CBaseCombatWeapon*)(DWORD)gInterface.EntityList()->GetClientEntityFromHandle(this->GetWeaponHandle());
	return weaponEntity->GetBulletsInClip();
}

bool CBaseEntity::HasGun()
{
	for (const auto& weapon : Weapons::guns)
		if (this->GetWeapon() == weapon)
			return true;

	return false;
}

bool CBaseEntity::HasAutoGun()
{
	for (const auto& weapon : Weapons::automatic)
		if (this->GetWeapon() == weapon)
			return true;

	return false;
}

bool CBaseEntity::CanShoot()
{
	float predictedCurrentTime = this->GetTickBase() * gInterface.Globals()->interval_per_tick;
	
	if (predictedCurrentTime >= this->GetNextAttack() && this->GetWeapClip() && !(this->GetFlags() & FL_ATCONTROLS))
		return true;

	return false;
}

player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t info;
	gInterface.Engine()->GetPlayerInfo(this->GetIndex(), &info);
	return info;
}

float CBaseEntity::GetSimulationTime()
{
	return gUtils.ReadAdress<float>(this, Offsets::m_flSimulationTime);
}
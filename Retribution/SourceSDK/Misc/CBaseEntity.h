#pragma once
#include "../sdk.h"

class CBaseEntity 
{
public:
	int GetIndex();
	bool GetDormant();
	int GetTeamNumber();
	int GetHealth();
	int GetFlags();
	Vector GetEyePosition();
	Vector& GetAbsOrigin();
	Vector GetVelocity();
	Vector GetBonePosition(int _boneId);
	QAngle GetAimPunchAngle();
	int GetShotsFired();
	DWORD GetWeaponHandle();
	int GetTickBase();
	float GetNextAttack();
	bool IsVisible(CBaseEntity* _localPlayer, int _boneId);
	bool IsValidTarget(CBaseEntity* _localPlayer, bool _targetTeammates, bool _targetPlayersInAir, bool _targetOnlyVisiblePlayers, int _visibleBoneId);
	int GetWeapon();
	int GetWeapClip();
	bool HasGun();
	bool HasAutoGun();
	bool CanShoot();
	player_info_t GetPlayerInfo();
	float GetSimulationTime();
};
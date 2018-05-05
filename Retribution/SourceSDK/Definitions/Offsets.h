#pragma once
#include <Windows.h>

namespace Offsets
{
	const DWORD m_isDormant = 0xE9;
	const DWORD m_iTeamNum = 0xF0;
	const DWORD m_iHealth = 0xFC;
	const DWORD m_fFlags = 0x100;
	const DWORD m_vecViewOffset = 0x104;
	const DWORD m_vecVelocity = 0x110;
	const DWORD m_dwBoneMatrix = 0x2698;
	const DWORD m_aimPunchAngle = 0x301C;
	const DWORD m_iShotsFired = 0xA2B0;
	const DWORD m_iItemDefinitionIndex = 0x2F88;
	const DWORD m_hActiveWeapon = 0x2EE8;
	const DWORD m_nTickBase = 0x3404;
	const DWORD m_flNextAttack = 0x2D60;
	const DWORD m_iClip1 = 0x3204;
	const DWORD m_flSimulationTime = 0x264;
}
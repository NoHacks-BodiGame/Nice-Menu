#pragma once
#include <vector>

namespace Weapons
{
	const int WEAPON_DEAGLE = 1;
	const int WEAPON_ELITE = 2;
	const int WEAPON_FIVESEVEN = 3;
	const int WEAPON_GLOCK = 4;
	const int WEAPON_AK47 = 7;
	const int WEAPON_AUG = 8;
	const int WEAPON_AWP = 9;
	const int WEAPON_FAMAS = 10;
	const int WEAPON_G3SG1 = 11;
	const int WEAPON_GALILAR = 13;
	const int WEAPON_M249 = 14;
	const int WEAPON_M4A1 = 16;
	const int WEAPON_MAC10 = 17;
	const int WEAPON_P90 = 19;
	const int WEAPON_UMP45 = 24;
	const int WEAPON_XM1014 = 25;
	const int WEAPON_BIZON = 26;
	const int WEAPON_MAG7 = 27;
	const int WEAPON_NEGEV = 28;
	const int WEAPON_SAWEDOFF = 29;
	const int WEAPON_TEC9 = 30;
	const int WEAPON_TASER = 31;
	const int WEAPON_HKP2000 = 32;
	const int WEAPON_MP7 = 33;
	const int WEAPON_MP9 = 34;
	const int WEAPON_NOVA = 35;
	const int WEAPON_P250 = 36;
	const int WEAPON_SCAR20 = 38;
	const int WEAPON_SG556 = 39;
	const int WEAPON_SSG08 = 40;
	const int WEAPON_KNIFE = 42;
	const int WEAPON_FLASHBANG = 43;
	const int WEAPON_HEGRENADE = 44;
	const int WEAPON_SMOKEGRENADE = 45;
	const int WEAPON_MOLOTOV = 46;
	const int WEAPON_DECOY = 47;
	const int WEAPON_INCGRENADE = 48;
	const int WEAPON_C4 = 49;
	const int WEAPON_KNIFE_T = 59;
	const int WEAPON_M4A1_SILENCER = 60;
	const int WEAPON_USP_SILENCER = 61;
	const int WEAPON_CZ75A = 63;
	const int WEAPON_REVOLVER = 64;
	const int WEAPON_KNIFE_BAYONET = 500;
	const int WEAPON_KNIFE_FLIP = 505;
	const int WEAPON_KNIFE_GUT = 506;
	const int WEAPON_KNIFE_KARAMBIT = 507;
	const int WEAPON_KNIFE_M9_BAYONET = 508;
	const int WEAPON_KNIFE_TACTICAL = 509;
	const int WEAPON_KNIFE_FALCHION = 512;
	const int WEAPON_KNIFE_SURVIVAL_BOWIE = 514;
	const int WEAPON_KNIFE_BUTTERFLY = 515;
	const int WEAPON_KNIFE_PUSH = 516;

	const std::vector<int>automatic
	{
		WEAPON_AK47,
		WEAPON_M4A1,
		WEAPON_M4A1_SILENCER,
		WEAPON_SG556,
		WEAPON_AUG,
		WEAPON_GALILAR,
		WEAPON_FAMAS,
		WEAPON_G3SG1,
		WEAPON_SCAR20,
		WEAPON_M249,
		WEAPON_NEGEV,
		WEAPON_MAC10,
		WEAPON_P90,
		WEAPON_UMP45,
		WEAPON_BIZON,
		WEAPON_MP7,
		WEAPON_MP9,
		WEAPON_CZ75A
	};

	const std::vector<int>bolt_action
	{
		WEAPON_AWP,
		WEAPON_SSG08
	};

	const std::vector<int>guns
	{
		WEAPON_AK47,
		WEAPON_M4A1,
		WEAPON_M4A1_SILENCER,
		WEAPON_SG556,
		WEAPON_AUG,
		WEAPON_GALILAR,
		WEAPON_FAMAS,
		WEAPON_G3SG1,
		WEAPON_SCAR20,
		WEAPON_M249,
		WEAPON_NEGEV,
		WEAPON_MAC10,
		WEAPON_P90,
		WEAPON_UMP45,
		WEAPON_BIZON,
		WEAPON_MP7,
		WEAPON_MP9,
		WEAPON_CZ75A,
		WEAPON_USP_SILENCER,
		WEAPON_HKP2000,
		WEAPON_GLOCK,
		WEAPON_P250,
		WEAPON_FIVESEVEN,
		WEAPON_TEC9,
		WEAPON_ELITE,
		WEAPON_DEAGLE,
		WEAPON_REVOLVER,
		WEAPON_NOVA,
		WEAPON_XM1014,
		WEAPON_MAG7,
		WEAPON_SAWEDOFF,
		WEAPON_SSG08,
		WEAPON_AWP
	};
}
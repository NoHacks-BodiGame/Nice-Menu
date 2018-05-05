#pragma once
#include "..\..\SourceSDK\sdk.h"
#include "SprayAssist.h"
#include "Backtracking.h"

class LegitBot
{
	friend class Hook;
	friend class Menu;
protected:
	bool Run(CUserCmd* _cmd, CBaseEntity* _localPlayer);
	void Reset();
protected:
	SprayAssist sprayAssist;
	Backtracking backtracking;
protected:
	float lockFov = 13.f;
	float unlockFov = 28.f;
	int startBullet = 2;
	int bestBone = Bones::head;
	int maxTick = 8;
};

extern LegitBot gLegitBot;

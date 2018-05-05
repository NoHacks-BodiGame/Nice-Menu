#pragma once
#include "..\..\SourceSDK\sdk.h"

struct BacktrackData
{
	Vector headPosition;
	float simulationTime;
};

class Backtracking
{
	friend class LegitBot;
	friend class Menu;
protected:
	bool Run(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick);
protected:
	bool active;
private:
	void GetBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick);
	bool BacktrackBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick);
private:
	int bestTarget = -1;
	BacktrackData entityPostionData[64][12];
};
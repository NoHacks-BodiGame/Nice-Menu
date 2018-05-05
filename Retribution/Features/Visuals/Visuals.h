#pragma once
#include "..\..\SourceSDK\sdk.h"

class Visuals
{
public:
	bool DrawEnemies(CBaseEntity* _localPlayer);
public:
	bool active;
};

extern Visuals gVisuals;
#pragma once
#include "..\..\SourceSDK\sdk.h"

class Bhop
{
	friend class Menu;
public:
	bool Run(CUserCmd* _cmd, CBaseEntity* _localPlayer);
protected:
	bool active = true;
};

extern Bhop gBhop;
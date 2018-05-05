#include "Bhop.h"

Bhop gBhop;

bool Bhop::Run(CUserCmd* _cmd, CBaseEntity* _localPlayer)
{
	if (!this->active)
		return false;

	if (_cmd->buttons & IN_JUMP && !(_localPlayer->GetFlags() & FL_ONGROUND))
		_cmd->buttons &= ~IN_JUMP;

	return true;
}
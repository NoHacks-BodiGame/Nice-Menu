#include "Hooks.h"

Hook::CreateMoveFn Hook::OriginalCreateMove;

bool __stdcall Hook::HookedCreateMove(float _inputSampleTime, CUserCmd* _cmd)
{
	OriginalCreateMove(_inputSampleTime, _cmd);
	gInterface.Engine()->SetViewAngles(_cmd->viewangles);

	if (!_cmd->command_number)	
		return true;
	
	CBaseEntity* localPlayer = gInterface.EntityList()->GetClientEntity(gInterface.Engine()->GetLocalPlayer());

	if (localPlayer->GetHealth())
	{
		gLegitBot.Run(_cmd, localPlayer);
		gBhop.Run(_cmd, localPlayer);
	}

	return false;
}
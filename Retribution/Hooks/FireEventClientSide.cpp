#include "Hooks.h"

Hook::FireEventClientSideFn Hook::OriginalFireEventClientSide;

bool __fastcall Hook::HookedFireEventClientSide(void* ecx, void* edx, IGameEvent *event)
{
	if (event)
	{
		if (!strcmp(event->GetName(), "round_start"))
		{
			gLegitBot.Reset();
		}

		if (!strcmp(event->GetName(), "player_death"))
		{
			int dead_player_id = event->GetInt("userid");

			CBaseEntity* localPlayer = gInterface.EntityList()->GetClientEntity(gInterface.Engine()->GetLocalPlayer());

			if (localPlayer && localPlayer->GetPlayerInfo().userID == dead_player_id)
			{
				gLegitBot.Reset();
			}
		}
		
		if (!strcmp(event->GetName(), "player_spawned"))
		{
			int spawnedPlayerId = event->GetInt("userid");

			CBaseEntity* localPlayer = gInterface.EntityList()->GetClientEntity(gInterface.Engine()->GetLocalPlayer());

			if (localPlayer && localPlayer->GetPlayerInfo().userID == spawnedPlayerId)
			{
				gLegitBot.Reset();
			}
		}
	}

	return OriginalFireEventClientSide(ecx, event);
}
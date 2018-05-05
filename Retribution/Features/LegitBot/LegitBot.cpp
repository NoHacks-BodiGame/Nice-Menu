#include "LegitBot.h"

LegitBot gLegitBot;

bool LegitBot::Run(CUserCmd* _cmd, CBaseEntity* _localPlayer)
{
	this->sprayAssist.Run(_cmd,_localPlayer,this->lockFov,this->unlockFov,this->bestBone, this->startBullet);
	
	if(!this->sprayAssist.active || !_localPlayer->HasAutoGun())
		this->backtracking.Run(_cmd, _localPlayer, this->maxTick);

	return true;
}

void LegitBot::Reset()
{
	if(this->sprayAssist.active)
		this->sprayAssist.Reset();
}
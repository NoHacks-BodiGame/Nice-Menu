#include "Backtracking.h"

bool Backtracking::Run(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick)
{
	if (!this->active)
		return false;
	
	if (this->bestTarget == -1)
		this->GetBestTarget(_cmd, _localPlayer, _maxTick);

	if (this->bestTarget != -1 && _cmd->buttons & IN_ATTACK && _localPlayer->HasGun())
		this->BacktrackBestTarget(_cmd, _localPlayer, _maxTick);
	
	this->bestTarget = -1;

	return true;
}

void Backtracking::GetBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick)
{
	float bestFov = 180.f;
		
	QAngle localViewAngles = _cmd->viewangles + _localPlayer->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < gInterface.Engine()->GetMaxClients(); ++i)
	{
		CBaseEntity* entity = gInterface.EntityList()->GetClientEntity(i);

		if (!entity->IsValidTarget(_localPlayer, false, true, false, 0))
			continue;

		Vector targetsHeadPosition = entity->GetBonePosition(Bones::head);
		QAngle aimAngle = gMath.CalculateAngle(_localPlayer->GetEyePosition(), targetsHeadPosition);
			
		float fov = gMath.GetFOV(localViewAngles, aimAngle);

		if (bestFov > fov)
		{
			this->bestTarget = i;
			bestFov = fov;
		}
		
		this->entityPostionData[i][_cmd->command_number % _maxTick] = { targetsHeadPosition, entity->GetSimulationTime() };
	}
}

bool Backtracking::BacktrackBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _maxTick)
{
	float bestSimulationTime = 0.f;
	float bestFov = 180.f;
		
	QAngle localViewAngles = _cmd->viewangles + _localPlayer->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < _maxTick; ++i)
	{
		if (!this->entityPostionData[this->bestTarget][i].simulationTime)
			continue;
				
		QAngle aimAngle = gMath.CalculateAngle(_localPlayer->GetEyePosition(), this->entityPostionData[this->bestTarget][i].headPosition);
		float fov = gMath.GetFOV(localViewAngles, aimAngle);

		if (bestFov > fov)
		{
			bestSimulationTime = this->entityPostionData[this->bestTarget][i].simulationTime;
			bestFov = fov;
		}
	}

	if (!bestSimulationTime)
		return false;

	_cmd->tick_count = gUtils.TimeToTicks(bestSimulationTime);
	return true;
}
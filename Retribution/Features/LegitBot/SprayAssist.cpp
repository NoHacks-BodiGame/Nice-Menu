#include "SprayAssist.h"

bool SprayAssist::Run(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _lockFov, float _unlockFov, int _bestBone, int _startBullet)
{
	if (!this->active)
		return false;

	if (this->bestTarget != -1)
		this->CheckBestTarget(_cmd, _localPlayer,_unlockFov,_bestBone);

	if (this->bestTarget == -1)
		this->GetBestTarget(_cmd, _localPlayer,_lockFov,_bestBone);

	if (this->bestTarget != -1 && _cmd->buttons & IN_ATTACK && _localPlayer->HasAutoGun() && _localPlayer->CanShoot() && _localPlayer->GetShotsFired() >= _startBullet)
		this->RunAimbot(_cmd, _localPlayer,_bestBone);
	else
		this->DropBestTarget();

	if (this->anglesAreChanged)
	{
		if (_localPlayer->GetFlags() & FL_ATCONTROLS)
			this->ChangeViewAngles(_cmd, lastChangedAngles);
		else
		{
			if (this->bestTarget == -1)
				this->FakeCrosshairMovement(_cmd);
		}
	}

	return true;
}

void SprayAssist::CheckBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _unlockFov, int _bestBone)
{
	CBaseEntity* bestEntity = gInterface.EntityList()->GetClientEntity(this->bestTarget);

	if (!bestEntity->IsValidTarget(_localPlayer, false, false, true, _bestBone))
	{
		this->DropBestTarget();
		return;
	}

	QAngle localViewAngles = _cmd->viewangles + _localPlayer->GetAimPunchAngle() * 2.f;
	Vector localEyePosition = _localPlayer->GetEyePosition();
	
	Vector bestTargetsBonePosition = bestEntity->GetBonePosition(_bestBone);
	QAngle aimAngle = gMath.CalculateAngle(localEyePosition, bestTargetsBonePosition);

	float distance = gMath.GetDistance(localEyePosition, bestTargetsBonePosition);
	float fov = gMath.GetDistanceBasedFOV(localViewAngles, aimAngle, distance);

	if (fov > _unlockFov)
		this->DropBestTarget();
}

void SprayAssist::DropBestTarget()
{
	this->bestTarget = -1;
	this->smooth = this->maxSmooth;
}

void SprayAssist::GetBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _lockFov, int _bestBone)
{
	float bestFov = _lockFov;

	Vector localEyePosition = _localPlayer->GetEyePosition();
	QAngle localViewAngles = _cmd->viewangles + _localPlayer->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < gInterface.Engine()->GetMaxClients(); ++i)
	{
		CBaseEntity* entity = gInterface.EntityList()->GetClientEntity(i);

		if (!entity->IsValidTarget(_localPlayer, false, false, true, _bestBone))
			continue;

		Vector targetsBonePosition = entity->GetBonePosition(_bestBone);
		QAngle aimAngle = gMath.CalculateAngle(localEyePosition, targetsBonePosition);

		float distance = gMath.GetDistance(localEyePosition, targetsBonePosition);
		float fov = gMath.GetDistanceBasedFOV(localViewAngles, aimAngle, distance);

		if (bestFov > fov)
		{
			this->bestTarget = i;
			bestFov = fov;
		}
	}
}

void SprayAssist::RunAimbot(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _bestBone)
{
	CBaseEntity* bestEntity = gInterface.EntityList()->GetClientEntity(this->bestTarget);
	
	Vector bestTargetsBonePosition = bestEntity->GetBonePosition(_bestBone);
	QAngle aimAngle = gMath.CalculateAngle(_localPlayer->GetEyePosition(), bestTargetsBonePosition);

	if (_localPlayer->GetShotsFired() > 1)
		aimAngle -= _localPlayer->GetAimPunchAngle() * 2.f;

	QAngle smoothAngle = this->GetSmoothAngle(_cmd->viewangles, aimAngle, &this->smooth, this->smoothDecr);
	this->ChangeViewAngles(_cmd, smoothAngle);

	this->anglesAreChanged = true;
	this->lastChangedAngles = _cmd->viewangles;
	this->fSmooth = this->maxFSmooth;
}

QAngle SprayAssist::GetSmoothAngle(const QAngle _from, const QAngle _to, float* _smooth, const float _decr)
{
	QAngle smoothAngle = _to;

	QAngle delta = _to - _from;
	delta.ClampAngles();

	if (!delta.IsZero())
	{
		if (*_smooth - _decr > 1.f)
			*_smooth -= _decr;
		else
			*_smooth = 1.f;

		QAngle step = delta / *_smooth;
		smoothAngle = _from + step;
	}

	return smoothAngle;
}

void SprayAssist::ChangeViewAngles(CUserCmd* _cmd, QAngle _value)
{
	_value.ClampAngles();
	_cmd->viewangles = _value;
}

void SprayAssist::FakeCrosshairMovement(CUserCmd* _cmd)
{
	QAngle fSmoothAngle = GetSmoothAngle(this->lastChangedAngles, _cmd->viewangles, &this->fSmooth, this->fSmoothDecr);

	if (gMath.GetFOV(fSmoothAngle, _cmd->viewangles) <= 0.03f)
		this->anglesAreChanged = false;

	this->ChangeViewAngles(_cmd, fSmoothAngle);
	this->lastChangedAngles = _cmd->viewangles;
}

void SprayAssist::Reset()
{
	this->bestTarget = -1;
	this->anglesAreChanged = false;
	this->smooth = this->maxSmooth;
	this->fSmooth = this->maxFSmooth;
	this->lastChangedAngles.Init(0, 0, 0);
}


#pragma once
#include "..\..\SourceSDK\sdk.h"

class SprayAssist
{
	friend class LegitBot;
	friend class Menu;
protected:
	bool Run(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _lockFov, float _unlockFov, int _bestBone, int _startBullet);
	void Reset();
protected:
	bool active;
private:
	void CheckBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _unlockFov, int _bestBone);
	void DropBestTarget();
	void GetBestTarget(CUserCmd* _cmd, CBaseEntity* _localPlayer, float _lockFov, int _bestBone);
	void RunAimbot(CUserCmd* _cmd, CBaseEntity* _localPlayer, int _bestBone);
	QAngle GetSmoothAngle(const QAngle _from, const QAngle _to, float* _smooth, const float _decr);
	void ChangeViewAngles(CUserCmd* _cmd, QAngle _value);
	void FakeCrosshairMovement(CUserCmd* _cmd);
private:
	float maxSmooth = 5.f;
	float smoothDecr = 0.35f;
	float maxFSmooth = 6.f;
	float fSmoothDecr = 0.15f;
private:
	int bestTarget = -1;
	float smooth = this->maxSmooth;
	float fSmooth = this->maxFSmooth;
	bool anglesAreChanged;
	QAngle lastChangedAngles;
};
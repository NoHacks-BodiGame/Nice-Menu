#include "Math.h"

Math gMath;

float Math::GetFOV(const QAngle &_from, const QAngle &_to)
{
	Vector fromVec = this->AngleToVector(_from);
	Vector toVec = this->AngleToVector(_to);
	
	return RAD2DEG(acos(fromVec.Dot(toVec) / fromVec.LengthSqr()));
}

float Math::GetDistanceBasedFOV(const QAngle &_from, const QAngle &_to, float _distance)
{
	Vector fromVec = this->AngleToVector(_from);
	fromVec *= _distance;

	Vector toVec = this->AngleToVector(_to);
	toVec *= _distance;

	return this->GetDistance(fromVec, toVec);
}

float Math::GetDistance(const Vector &_from, const Vector &_to)
{
	return (float)(sqrt(pow((_from.x - _to.x), 2) + pow((_from.y - _to.y), 2) + pow((_from.z - _to.z), 2)));
}

QAngle Math::CalculateAngle(const Vector &_from, const Vector &_to)
{
	Vector delta = _from - _to;
	return this->VectorToAngle(delta);
}

QAngle Math::VectorToAngle(const Vector& _vec)
{
	float tmp, yaw, pitch;

	if (!_vec.y && !_vec.x)
	{
		yaw = 0;
		if (_vec.z > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(_vec.y, _vec.x) * 180 / M_PI);

		if (yaw > 90)
			yaw -= 180;
		else if (yaw < 90)
			yaw += 180;
		else if (yaw == 90)
			yaw = 0;

		tmp = sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
		pitch = (atan2(_vec.z, tmp) * 180 / M_PI);
	}
	
	return QAngle(pitch, yaw, 0);
}

Vector Math::AngleToVector(const QAngle &_angle)
{
	float sp, sy, cp, cy;

	this->SinCos(DEG2RAD(_angle.y), &sy, &cy);
	this->SinCos(DEG2RAD(_angle.x), &sp, &cp);
		
	return Vector(cp*cy, cp*sy, -sp);
}

void Math::SinCos(float _radians, float* _sine, float* _cosine)
{
	*_sine = sin(_radians);
	*_cosine = cos(_radians);
}

bool Math::WorldToScreen(const Vector &_origin, Vector &_screen)
{
	if (this->ScreenTransform(_origin, _screen))
		return false;

	int screenWidth, screenHeight;
	gInterface.Engine()->GetScreenSize(screenWidth, screenHeight);

	float x = screenWidth / 2.f;
	float y = screenHeight / 2.f;

	x += 0.5f * _screen.x * screenWidth + 0.5f;
	y -= 0.5f * _screen.y * screenHeight + 0.5f;

	_screen.x = x;
	_screen.y = y;
	
	return true;
}

bool Math::ScreenTransform(const Vector &_point, Vector &_screen)
{
	return this->FrustumTransform(gInterface.Engine()->WorldToScreenMatrix(), _point, _screen);
}

bool Math::FrustumTransform(const VMatrix &_worldToSurface, const Vector &_point, Vector &_screen)
{
	float w;

	_screen.x = _worldToSurface[0][0] * _point[0] + _worldToSurface[0][1] * _point[1] + _worldToSurface[0][2] * _point[2] + _worldToSurface[0][3];
	_screen.y = _worldToSurface[1][0] * _point[0] + _worldToSurface[1][1] * _point[1] + _worldToSurface[1][2] * _point[2] + _worldToSurface[1][3];

	w = _worldToSurface[3][0] * _point[0] + _worldToSurface[3][1] * _point[1] + _worldToSurface[3][2] * _point[2] + _worldToSurface[3][3];

	_screen.z = 0.0f;

	bool behind;
	
	if (w < 0.001f)
	{
		behind = true;
		_screen.x *= 100000;
		_screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		_screen.x *= invw;
		_screen.y *= invw;
	}

	return behind;
}
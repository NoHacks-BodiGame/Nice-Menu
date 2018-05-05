#pragma once
#include "Vector.h"
#include "VMatrix.h"
#include "..\Interfaces\Engine.h"

#define M_PI		3.14159265358979323846
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / (float)M_PI) )
#define DEG2RAD( x  )  ( (float)(x) * (float)((float)M_PI / 180.f) )

class Math
{
public:
	float GetFOV(const QAngle &_from, const QAngle &_to);
	float GetDistanceBasedFOV(const QAngle &_from, const QAngle &_to, float _distance);
	float GetDistance(const Vector &_from, const Vector &_to);
	QAngle CalculateAngle(const Vector &_from, const Vector &_to);
	QAngle VectorToAngle(const Vector &_vec);
	Vector AngleToVector(const QAngle &_angle);
	bool WorldToScreen(const Vector &_origin, Vector &_screen);
private:
	void SinCos(float _radians, float* _sine, float* _cosine);
	bool ScreenTransform(const Vector &_point, Vector &_screen);
	bool FrustumTransform(const VMatrix &_worldToSurface, const Vector &_point, Vector &_screen);
};

extern Math gMath;
#pragma once
#include <string>
#include <sstream>
#include "..\Interfaces\Interfaces.h"
#include "..\Interfaces\EngineTrace.h"
#include "..\Interfaces\Globals.h"
#include "Paint.h"
#include "Controls.h"

class CBaseEntity;

class Utils
{
public:
	trace_t TraceRay(Vector _from, Vector _to, CBaseEntity* _skip, DWORD _mask);
public:
	inline int TimeToTicks(const float _time)
	{
		return (int)(0.5f + (float)(_time) / gInterface.Globals()->interval_per_tick);
	}
public:
	template<class C, typename T>
	C inline ReadAdress(T _base, DWORD _offset)
	{
		return (_base) ? *(C*)((DWORD)_base + _offset) : 0;
	}

	template <typename T>
	T ClampValue(T _value, T _minValue, T _maxValue)
	{
		if (_value < _minValue)
			_value = _minValue;
		else if (_value > _maxValue)
			_value = _maxValue;

		return _value;
	}
	
	template <typename T>
	std::string ToStringWithPrecision(T _value, int _precision)
	{
		std::ostringstream out;
		out << std::fixed << std::setprecision(_precision) << _value;
		return out.str();
	}
};

extern Utils gUtils;
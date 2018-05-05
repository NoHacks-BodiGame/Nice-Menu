#include "Utils.h"

Utils gUtils;

trace_t Utils::TraceRay(Vector _from, Vector _to, CBaseEntity* _skip, DWORD _mask)
{
	Ray_t ray;
	trace_t trace;

	ray.Init(_from, _to);

	CTrace_Filter Filter;
	Filter.pSkip = _skip;

	gInterface.EngineTrace()->TraceRay(ray, _mask, &Filter, &trace);
	
	return trace;
}

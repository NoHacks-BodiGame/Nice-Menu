#pragma once
#include "..\Misc\EngineTraceStructs.h"

class IEngineTrace
{
public:
	inline void TraceRay(const Ray_t &_ray, unsigned int _mask, ITrace_Filter *_traceFilter, trace_t *_trace);
};

inline void IEngineTrace::TraceRay(const Ray_t &_ray, unsigned int _mask, ITrace_Filter *_traceFilter, trace_t *_trace)
{
	return gInterface.CallVirtualFunction<void>(this, Indexes::EngineTrace::TraceRay, std::ref(_ray), _mask, _traceFilter, _trace);
}
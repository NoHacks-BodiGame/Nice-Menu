#include "Hooks.h"

Hook::InternalCursorMovedFn Hook::OriginalInternalCursorMoved;

bool __fastcall Hook::HookedInternalCursorMoved(void* ecx, void* edx, int x, int y)
{
	if (gMenu.IsActive())
		return true;
		
	return OriginalInternalCursorMoved(ecx, x, y);
}
#include "Hooks.h"

Hook::InternalMouseDoublePressedFn Hook::OriginalInternalMouseDoublePressed;

bool __fastcall Hook::HookedInternalMouseDoublePressed(void* ecx, void* edx, ButtonCode_t code)
{
	if (gMenu.IsActive())
		return true;

	return OriginalInternalMouseDoublePressed(ecx, code);
}
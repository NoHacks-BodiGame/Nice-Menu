#include "Hooks.h"

Hook::InternalMousePressedFn Hook::OriginalInternalMousePressed;

bool __fastcall Hook::HookedInternalMousePressed(void* ecx, void* edx, ButtonCode_t code)
{
	if (gMenu.IsActive())
		return true;

	return OriginalInternalMousePressed(ecx, code);
}
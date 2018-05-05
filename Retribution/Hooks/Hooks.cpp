#include "Hooks.h"

void Hook::SetupHooks()
{
	VMTHookManager clientModeHook(gInterface.ClientMode());
	this->HookVirtualFunction(clientModeHook, Indexes::ClientMode::CreateMove, this->HookedCreateMove, &this->OriginalCreateMove);

	VMTHookManager panelHook(gInterface.Panel());
	this->HookVirtualFunction(panelHook, Indexes::Panel::PaintTraverse, this->HookedPaintTraverse, &this->OriginalPaintTraverse);

	VMTHookManager gameEventHook(gInterface.GameEvent());
	this->HookVirtualFunction(gameEventHook, Indexes::GAMEEVENTSMANAGER::FireEventClientSide, this->HookedFireEventClientSide, &this->OriginalFireEventClientSide);

	VMTHookManager inputInternalHook(gInterface.InputInternal());
	this->HookVirtualFunction(inputInternalHook, Indexes::InputInternal::InternalCursorMoved, this->HookedInternalCursorMoved, &this->OriginalInternalCursorMoved);
	this->HookVirtualFunction(inputInternalHook, Indexes::InputInternal::InternalMousePressed, this->HookedInternalMousePressed, &this->OriginalInternalMousePressed);
	this->HookVirtualFunction(inputInternalHook, Indexes::InputInternal::InternalMouseDoublePressed, this->HookedInternalMouseDoublePressed, &this->OriginalInternalMouseDoublePressed);
};


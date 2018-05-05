#pragma once
#include "..\SourceSDK\Utils\VMTHookManager.h"
#include "..\SourceSDK\sdk.h"
#include "..\Menu\Menu.h"
#include "..\Features\LegitBot\LegitBot.h"
#include "..\Features\Misc\Bhop.h"
#include "..\Features\Visuals\Visuals.h"

class Hook
{
public:
	void SetupHooks();
private:
	typedef bool(__stdcall* CreateMoveFn)(float, CUserCmd*);
	static CreateMoveFn OriginalCreateMove;
	static bool __stdcall HookedCreateMove(float _inputSampleTime, CUserCmd* _cmd);
private:
	typedef void(__stdcall* PaintTraverseFn)(VPANEL, bool, bool);
	static PaintTraverseFn OriginalPaintTraverse;
	static void __stdcall HookedPaintTraverse(VPANEL _vguiPanel, bool _forceRepaint, bool _allowForce);
private:
	typedef bool(__thiscall* FireEventClientSideFn)(void*, IGameEvent*);
	static FireEventClientSideFn OriginalFireEventClientSide;
	static bool __fastcall HookedFireEventClientSide(void* ecx, void* edx, IGameEvent *event);
private:
	typedef bool(__thiscall* InternalCursorMovedFn)(void*, int, int);
	static InternalCursorMovedFn OriginalInternalCursorMoved;
	static bool __fastcall HookedInternalCursorMoved(void* ecx, void* edx, int x, int y);
private:
	typedef bool(__thiscall* InternalMousePressedFn)(void*, ButtonCode_t);
	static InternalMousePressedFn OriginalInternalMousePressed;
	static bool __fastcall HookedInternalMousePressed(void* ecx, void* edx, ButtonCode_t code);
private:
	typedef bool(__thiscall* InternalMouseDoublePressedFn)(void*, ButtonCode_t);
	static InternalMouseDoublePressedFn OriginalInternalMouseDoublePressed;
	static bool __fastcall HookedInternalMouseDoublePressed(void* ecx, void* edx, ButtonCode_t code);
private:
	template<typename T, typename F>
	void HookVirtualFunction(VMTHookManager &_vmtHook, int _functionIndex, const T &_hookedFunction, F *_originalFunction)
	{
		_vmtHook.HookFunction(_functionIndex, _hookedFunction);
		*_originalFunction = (F)_vmtHook.GetOriginalFunction(_functionIndex);
	}
};
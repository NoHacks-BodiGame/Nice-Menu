#include <Windows.h>
#include "Hooks\Hooks.h"

void Main()
{
	while (!GetModuleHandle("serverbrowser.dll"))	// Wait for game to load completely
		Sleep(100);
	
	Hook hook;
	hook.SetupHooks();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Main, NULL, NULL, NULL);

	return TRUE;
}
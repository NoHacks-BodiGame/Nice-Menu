#include "Interfaces.h"

Interface gInterface;

IBaseClientDLL* Interface::Client()
{
	if(!this->clientInterface)
		this->clientInterface = this->FindInterface<IBaseClientDLL>("client.dll", "VClient");

	return this->clientInterface;
}

ClientModeShared* Interface::ClientMode()
{
	if (!this->clientModeInterface)
		this->clientModeInterface = **(ClientModeShared***)((*(DWORD**)this->Client())[10] + 0x5);

	return this->clientModeInterface;
}

IVEngineClient* Interface::Engine()
{
	if (!this->engineInterface)
		this->engineInterface = this->FindInterface<IVEngineClient>("engine.dll", "VEngineClient");

	return this->engineInterface;
}

IClientEntityList* Interface::EntityList()
{
	if (!this->entityListInterface)
		this->entityListInterface = this->FindInterface<IClientEntityList>("client.dll", "VClientEntityList");

	return this->entityListInterface;
}

IEngineTrace* Interface::EngineTrace()
{
	if (!this->engineTraceInterface)
		this->engineTraceInterface = this->FindInterface<IEngineTrace>("engine.dll", "EngineTraceClient");

	return this->engineTraceInterface;
}

IPanel* Interface::Panel()
{
	if (!this->panelInterface)
		this->panelInterface = this->FindInterface<IPanel>("vgui2.dll", "VGUI_Panel");

	return this->panelInterface;
}

ISurface* Interface::Surface()
{
	if (!this->surfaceInterface)
		this->surfaceInterface = this->FindInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface");

	return this->surfaceInterface;
}

IInputSystem* Interface::InputSystem()
{
	if (!this->inputSystemInterface)
		this->inputSystemInterface = this->FindInterface<IInputSystem>("inputsystem.dll", "InputSystemVersion");

	return this->inputSystemInterface;
}

IInputInternal* Interface::InputInternal()
{
	if (!this->inputInternalInterface)
		this->inputInternalInterface = this->FindInterface<IInputInternal>("vgui2.dll", "VGUI_InputInternal");
	
	return this->inputInternalInterface;
}

IGameEvent* Interface::GameEvent()
{
	if (!this->gameEventInterface)
	{
		typedef void* (*CreateInterfaceFn)(const char*, int*);
		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
		
		this->gameEventInterface = (IGameEvent*)CreateInterface("GAMEEVENTSMANAGER002", NULL);
	}

	return this->gameEventInterface;
}

CGlobalVarsBase* Interface::Globals()
{
	if(!this->GlobalsInterface)
		this->GlobalsInterface = **(CGlobalVarsBase***)((*(DWORD**)this->Client())[0] + 0x1B);

	return this->GlobalsInterface;
}